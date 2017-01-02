#include <iostream>
#include <stdexcept>
#include <string>

#include "modulefunctionloader.hh"
#include "modulerepository.hh"

typedef int (*entry_function)();


int main(int argc, char **argv)
{
    if (argc < 3)
        return 0;

    const char *path = argv[1];
    const char *entry_name = argv[2];

    SharedLibraryRepository sharedLibraryRepository;
    ModuleRepository moduleRepository = ModuleRepository(&sharedLibraryRepository);

    ModuleFunctionLoader *module = moduleRepository.getModule(path);

    entry_function entry = (entry_function)(module)->loadFunction(entry_name);

    return entry();
}
