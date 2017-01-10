#pragma once

#include "callable.hh"

class ModuleFunctionLoader
{
public:
    virtual Callable *loadFunction(const char *functionName) = 0;
};
