#pragma once

#include <string>

#include "module.hh"
#include "util/repository.hh"

class ModuleRepository
{
public:
    void save(const std::string &key, Module *module);
    void remove(const std::string &key);

    Module *get(const std::string &key);

private:
    Repository _modules;
};
