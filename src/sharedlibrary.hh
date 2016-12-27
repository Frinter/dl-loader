#pragma once

class SharedLibrary
{
public:
    static SharedLibrary *create(const char *path);

public:
    virtual ~SharedLibrary()
    {
    }

    virtual void load() = 0;
    virtual void unload() = 0;
    virtual void *loadFunction(const char *functionName) = 0;

protected:
    SharedLibrary() {}
};
