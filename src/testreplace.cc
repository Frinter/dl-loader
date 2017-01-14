#include <iostream>
#include <cstdlib>

#include "loadparameters.hh"

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

        if (parameters->initialData != NULL)
        {
            ExportData *import = (ExportData *)parameters->initialData;
            data = import->data;
        }
        else
        {
            data = 15;
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

    void foo(void *params)
    {
        std::cout << "hello from lib replacement: " << data << std::endl;
    }
}
