#pragma once

#include "sharedlibrary.hh"

class Module
{
private:
    typedef void  (*onModuleLoad_function)(void *);
    typedef void *(*exportModuleData_function)();

public:
    Module(SharedLibrary *library);

    void load();
    void load(void *initialData);
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
