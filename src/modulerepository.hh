#pragma once

#include <string>

#include "sharedlibraryrepository.hh"
#include "util/repository.hh"

class ModuleRepository
{
public:
    ModuleRepository(SharedLibraryRepository *sharedLibraryRepository);

    ModuleFunctionLoader *getModule(const std::string &moduleName);

private:
    Repository _modules;
    SharedLibraryRepository *_sharedLibraryRepository;
};
