#include "modulerepository.hh"
#include "sharedlibraryrepository.hh"

ModuleRepository::ModuleRepository(SharedLibraryRepository *sharedLibraryRepository)
    : _sharedLibraryRepository(sharedLibraryRepository)
{
}

ModuleFunctionLoader *ModuleRepository::getModule(const char *moduleName)
{
    ModuleInfo *info = _findModule(moduleName);

    if (info != NULL)
        return (ModuleFunctionLoader *)info->module;

    SharedLibrary *library = _sharedLibraryRepository->get(moduleName);
    if (library == NULL)
    {
        library = SharedLibrary::create(moduleName);
        _sharedLibraryRepository->registerLibrary(moduleName, library);
    }

    Module *module = new Module(library);
    module->load();

    info = new ModuleInfo();
    info->name = moduleName;
    info->module = module;

    _modules.push_back(info);

    return (ModuleFunctionLoader *)module;
}

ModuleRepository::ModuleInfo *ModuleRepository::_findModule(const char *moduleName)
{
    for (int i = 0; i < _modules.size(); ++i)
    {
        if (_modules[i]->name == moduleName)
            return _modules[i];
    }

    return NULL;
}
