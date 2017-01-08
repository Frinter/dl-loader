#pragma once

#include "sharedlibrary.hh"
#include "modulefunctionloader.hh"
#include "moduleinterfacerepository.hh"

class Module : public ModuleFunctionLoader
{
private:
    typedef void  (*onModuleLoad_function)(void *, ModuleInterfaceRepository *);
    typedef void *(*exportModuleData_function)();

public:
    Module(ModuleInterfaceRepository *modules, SharedLibrary *library);

    void load();
    void load(void *initialData);
    void unload();
    void reload();
    void reload(SharedLibrary *newLibrary);

    void *loadFunction(const char *functionName);

    void *getExportedData();

private:
    ModuleInterfaceRepository *_modules;

    SharedLibrary *_library;
    onModuleLoad_function _onModuleLoad;
    exportModuleData_function _exportModuleData;

    Module(const Module &o) = delete;
};
