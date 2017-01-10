#pragma once

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

    Callable *loadFunction(const char *functionName);

    void *getExportedData();

private:
    ModuleInterfaceRepository *_modules;

    SharedLibrary *_library;
    Callable *_onModuleLoad;
    Callable *_exportModuleData;

    Module(const Module &o) = delete;
};
