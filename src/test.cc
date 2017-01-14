#include <iostream>
#include <cstdlib>

#include "loadparameters.hh"
#include "modulefunctionloader.hh"
#include "moduleinterfacerepository.hh"

int data;

typedef struct
{
    int data;
} ExportData;

extern "C" {
    const char *getModuleName()
    {
        return "Test Module";
    }

    void onModuleLoad(void *params)
    {
        LoadParameters *parameters = (LoadParameters *)params;
        ModuleFunctionLoader *dependency = parameters->modules->getModuleInterface("bin/testDependency.dll");

        if (parameters->initialData != NULL)
        {
            ExportData *import = (ExportData *)parameters->initialData;
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
                int *value = (int*)dependency->callFunction("getValue");
                data = *value;
                delete value;
            }
        }
    }

    void *exportModuleData(void *params)
    {
        ExportData *exportData = (ExportData*)malloc(sizeof(ExportData));
        exportData->data = data;
        return (void*)exportData;
    }

    void setValue(int x)
    {
        data = x;
    }

    void *foo(void *params)
    {
        std::cout << "hello from lib: " << data << std::endl;
    }
}
