#pragma once

#include <string>

#include "module.hh"
#include "sharedlibraryrepository.hh"
#include "util/repository.hh"

class ModuleRepository
{
private:
    typedef struct {
        std::string name;
        Module *module;
    } ModuleInfo;

public:
    ModuleRepository(SharedLibraryRepository *sharedLibraryRepository);

    ModuleFunctionLoader *getModule(const std::string &moduleName);

private:
    Repository _modules;
    SharedLibraryRepository *_sharedLibraryRepository;
};
