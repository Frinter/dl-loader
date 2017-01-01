#pragma once

#include "sharedlibrary.hh"
#include "modulefunctionloader.hh"

class Module : public ModuleFunctionLoader
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
