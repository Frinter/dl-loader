#include "module.hh"
#include "sharedlibraryrepository.hh"

#include "modulerepository.hh"

ModuleRepository::ModuleRepository(SharedLibraryRepository *sharedLibraryRepository)
    : _sharedLibraryRepository(sharedLibraryRepository)
{
}

ModuleFunctionLoader *ModuleRepository::getModule(const std::string &moduleName)
{
    Module *module = (Module *)_modules.get(moduleName);

    if (module != NULL)
        return (ModuleFunctionLoader *)module;

    SharedLibrary *library = _sharedLibraryRepository->get(moduleName);
    if (library == NULL)
    {
        library = SharedLibrary::create(moduleName.c_str());
        _sharedLibraryRepository->registerLibrary(moduleName, library);
    }

    module = new Module(library);
    module->load();

    _modules.save(moduleName, (void *)module);

    return (ModuleFunctionLoader *)module;
}
