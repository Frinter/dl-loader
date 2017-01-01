#pragma once

class ModuleFunctionLoader
{
public:
    virtual void *loadFunction(const char *functionName) = 0;
};
