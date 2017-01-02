#pragma once

#include <string>
#include <vector>

#include "module.hh"
#include "sharedlibraryrepository.hh"

class ModuleRepository
{
private:
    typedef struct {
        std::string name;
        Module *module;
    } ModuleInfo;

public:
    ModuleRepository(SharedLibraryRepository *sharedLibraryRepository);

    ModuleFunctionLoader *getModule(const char *moduleName);

private:
    ModuleInfo *_findModule(const char *moduleName);

private:
    std::vector<ModuleInfo *> _modules;
    SharedLibraryRepository *_sharedLibraryRepository;
};
