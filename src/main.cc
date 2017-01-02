#include <iostream>
#include <stdexcept>
#include <string>

#include "modulefunctionloader.hh"
#include "modulerepository.hh"
#include "sharedlibraryrepository.hh"

typedef int (*entry_function)();


int main(int argc, char **argv)
{
    if (argc < 3)
        return 0;

    const char *path = argv[1];
    const char *entry_name = argv[2];

    SharedLibraryRepository sharedLibraryRepository;
    ModuleRepository moduleRepository;

    Module *module = moduleRepository.get(path);
    if (module == NULL)
    {
        SharedLibrary *library = sharedLibraryRepository.get(path);
        if (library == NULL)
        {
            library = SharedLibrary::create(path);
            sharedLibraryRepository.save(path, library);
        }

        module = new Module(library);
        module->load();

        moduleRepository.save(path, module);
    }

    ModuleFunctionLoader *moduleInterface = (ModuleFunctionLoader *)module;
    entry_function entry = (entry_function)moduleInterface->loadFunction(entry_name);

    return entry();
}
