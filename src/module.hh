#pragma once

#include "callable.hh"
#include "sharedlibrary.hh"
#include "modulefunctionloader.hh"
#include "moduleinterfacerepository.hh"

class Module : public ModuleFunctionLoader
{
public:
    Module(ModuleInterfaceRepository *modules, SharedLibrary *library);

    void load();
    void load(void *initialData);
    void unload();
    void reload();
    void reload(SharedLibrary *newLibrary);

    void *callFunction(const char *functionName);
    void *callFunction(const char *functionName, void *arguments);

    void *getExportedData();

private:
    Callable *loadFunction(const char *functionName);

private:
    ModuleInterfaceRepository *_modules;

    SharedLibrary *_library;
    Callable *_onModuleLoad;
    Callable *_exportModuleData;

    Module(const Module &o) = delete;
};
