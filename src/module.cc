#include <stdlib.h>

#include "module.hh"
#include "loadparameters.hh"

Module::Module(ModuleInterfaceRepository *modules, SharedLibrary *library)
    : _modules(modules), _library(library)
{
}

void Module::load()
{
    load(NULL);
}

void Module::load(void *initialData)
{
    _library->load();

    _onModuleLoad = loadFunction("onModuleLoad");
    _exportModuleData = loadFunction("exportModuleData");

    LoadParameters parameters;
    parameters.initialData = initialData;
    parameters.modules = _modules;

    _onModuleLoad->call(&parameters);
}

void *Module::getExportedData()
{
    return _exportModuleData->call(NULL);
}

void Module::unload()
{
    _library->unload();
}

void Module::reload()
{
    void *data = getExportedData();
    unload();
    load(data);
}

void Module::reload(SharedLibrary *newLibrary)
{
    void *data = getExportedData();
    unload();
    _library = newLibrary;
    load(data);
}

typedef void *(*callable_function)(void *);
class RegularCallable : public Callable
{
public:
    RegularCallable(callable_function function)
        : _function(function)
    {
    }

    void *call(void *arguments)
    {
        return _function(arguments);
    }

private:
    callable_function _function;
};

Callable *Module::loadFunction(const char *functionName)
{
    return new RegularCallable((callable_function)_library->loadFunction(functionName));
}
