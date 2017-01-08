#pragma once

#include <string>

#include "module.hh"
#include "moduleinterfacerepository.hh"
#include "util/repository.hh"

class ModuleRepository : public ModuleInterfaceRepository
{
public:
    void save(const std::string &key, Module *module);
    void remove(const std::string &key);

    Module *get(const std::string &key);
    ModuleFunctionLoader *getModuleInterface(const std::string &name);

private:
    Repository _modules;
};
