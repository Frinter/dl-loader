#pragma once

#include <string>

#include "modulefunctionloader.hh"

class ModuleInterfaceRepository
{
public:
    virtual ModuleFunctionLoader *getModuleInterface(const std::string &name) = 0;
};
