#include <stdlib.h>

#include "module.hh"

Module::Module(SharedLibrary *library)
    : _library(library)
{
}

void Module::load()
{
    load(NULL);
}

void Module::load(void *initialData)
{
    _library->load();

    _onModuleLoad = (onModuleLoad_function)loadFunction("onModuleLoad");
    _exportModuleData = (exportModuleData_function)loadFunction("exportModuleData");

    _onModuleLoad(initialData);
}

void *Module::getExportedData()
{
    return _exportModuleData();
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

void *Module::loadFunction(const char *functionName)
{
    return _library->loadFunction(functionName);
}
