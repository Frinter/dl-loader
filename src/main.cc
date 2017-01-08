#include <iostream>
#include <stdexcept>
#include <string>

#include "modulefunctionloader.hh"
#include "modulerepository.hh"
#include "sharedlibraryrepository.hh"
#include "moduleinterfacerepositoryimplementation.hh"

typedef int (*entry_function)();

SharedLibrary *getOrOpenSharedLibrary(const char *name, SharedLibraryRepository *sharedLibraryRepository)
{
    SharedLibrary *library = sharedLibraryRepository->get(name);
    if (library == NULL)
    {
        library = SharedLibrary::create(name);
        sharedLibraryRepository->save(name, library);
    }

    return library;
}

Module *getOrOpenModule(const char *name, ModuleRepository *moduleRepository, SharedLibraryRepository *sharedLibraryRepository)
{
    Module *module = moduleRepository->get(name);
    if (module == NULL)
    {
        SharedLibrary *library = getOrOpenSharedLibrary(name, sharedLibraryRepository);

        module = new Module((ModuleInterfaceRepository *)moduleRepository, library);
        module->load();

        moduleRepository->save(name, module);
    }

    return module;
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return 0;

    const char *path = argv[1];
    const char *entry_name = argv[2];

    SharedLibraryRepository sharedLibraryRepository;
    ModuleRepository moduleRepository;

    SharedLibrary *replaceLibrary = getOrOpenSharedLibrary("bin/testreplace.dll", &sharedLibraryRepository);

    Module *dependencyModule = getOrOpenModule("bin/testDependency.dll", &moduleRepository, &sharedLibraryRepository);
    Module *module = getOrOpenModule(path, &moduleRepository, &sharedLibraryRepository);

    ModuleFunctionLoader *moduleInterface = (ModuleFunctionLoader *)module;
    entry_function entry = (entry_function)moduleInterface->loadFunction(entry_name);
    entry();

    module->reload();
    moduleInterface = (ModuleFunctionLoader *)module;
    entry = (entry_function)moduleInterface->loadFunction(entry_name);
    entry();

    module->reload(replaceLibrary);
    sharedLibraryRepository.remove(path);
    entry = (entry_function)moduleInterface->loadFunction(entry_name);
    entry();

    return 0;
}
