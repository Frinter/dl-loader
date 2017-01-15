#include <iostream>
#include <stdexcept>
#include <string>

#include "command.hh"
#include "modulefunctionloader.hh"
#include "modulerepository.hh"
#include "mutex.hh"
#include "sharedlibraryrepository.hh"
#include "thread.hh"

typedef int (*entry_function)();

class DummyCommand : public Command
{
public:
    void execute()
    {
        dataLock->lock();
        std::cout << "from command" << std::endl;
        dataLock->unlock();
    }

public:
    Mutex *dataLock;
};

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
    moduleInterface->callFunction(entry_name);

    module->reload();
    moduleInterface = (ModuleFunctionLoader *)module;
    moduleInterface->callFunction(entry_name);

    module->reload(replaceLibrary);
    sharedLibraryRepository.remove(path);
    moduleInterface->callFunction(entry_name);

    DummyCommand *command = new DummyCommand();
    command->dataLock = Mutex::create();
    command->dataLock->lock();
    Thread *thread = Thread::create(command);
    std::cout << "still in main" << std::endl;
    command->dataLock->unlock();
    thread->join();

    return 0;
}
