#pragma once

#include "sharedlibrary.hh"

#ifndef NULL
# define NULL 0
#endif

class Module
{
private:
    typedef void  (*onModuleLoad_function)(void *);
    typedef void *(*exportModuleData_function)();

public:
    Module(SharedLibrary *library);

    void load(void *initialData = NULL);
    void unload();
    void reload();

    void *loadFunction(const char *functionName);

    void *getExportedData();

private:
    SharedLibrary *_library;
    onModuleLoad_function _onModuleLoad;
    exportModuleData_function _exportModuleData;

    Module(const Module &o) = delete;
};
