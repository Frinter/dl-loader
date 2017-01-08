#include <iostream>
#include <cstdlib>

#include "modulefunctionloader.hh"
#include "moduleinterfacerepository.hh"

int data;

typedef struct
{
    int data;
} ExportData;

typedef int (*getValue_function)();

getValue_function getValue;

extern "C" {
    typedef void (*foo_function)();

    const char *getModuleName()
    {
        return "Test Module";
    }

    void onModuleLoad(void *initialData, ModuleInterfaceRepository *modules)
    {
        ModuleFunctionLoader *dependency = modules->getModule("bin/testDependency.dll");

        if (initialData != NULL)
        {
            ExportData *import = (ExportData *)initialData;
            data = import->data;
        }
        else
        {
            if (dependency == NULL)
            {
                std::cout << "Failed to load dependency" << std::endl;
                data = 5;
            }
            else
            {
                std::cout << "Success loading dependency" << std::endl;
                getValue = (getValue_function)dependency->loadFunction("getValue");
                data = getValue();
            }
        }
    }

    void *exportModuleData()
    {
        ExportData *exportData = (ExportData*)malloc(sizeof(ExportData));
        exportData->data = data;
        return (void*)exportData;
    }

    void setValue(int x)
    {
        data = x;
    }

    void foo()
    {
        std::cout << "hello from lib: " << data << std::endl;
    }
}
