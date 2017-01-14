#pragma once

class ModuleFunctionLoader
{
public:
    virtual void *callFunction(const char *functionName) = 0;
    virtual void *callFunction(const char *functionName, void *arguments) = 0;
};
