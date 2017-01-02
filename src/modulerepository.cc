#include "modulerepository.hh"
#include "sharedlibraryrepository.hh"

ModuleRepository::ModuleRepository(SharedLibraryRepository *sharedLibraryRepository)
    : _sharedLibraryRepository(sharedLibraryRepository)
{
}

ModuleFunctionLoader *ModuleRepository::getModule(const std::string &moduleName)
{
    ModuleInfo *info = (ModuleInfo *)_modules.get(moduleName);

    if (info != NULL)
        return (ModuleFunctionLoader *)info->module;

    SharedLibrary *library = _sharedLibraryRepository->get(moduleName);
    if (library == NULL)
    {
        library = SharedLibrary::create(moduleName.c_str());
        _sharedLibraryRepository->registerLibrary(moduleName, library);
    }

    Module *module = new Module(library);
    module->load();

    info = new ModuleInfo();
    info->name = moduleName;
    info->module = module;

    _modules.save(moduleName, (void *)info);

    return (ModuleFunctionLoader *)module;
}
