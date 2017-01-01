#pragma once

#include <string>
#include <vector>

#include "module.hh"
#include "sharedlibrary.hh"

class ModuleRepository
{
private:
    typedef struct {
        std::string name;
        Module *module;
    } ModuleInfo;

public:
    ModuleRepository();

    ModuleFunctionLoader *getModule(const char *moduleName);

private:
    ModuleInfo *_findModule(const char *moduleName);

private:
    std::vector<ModuleInfo *> _modules;
};
