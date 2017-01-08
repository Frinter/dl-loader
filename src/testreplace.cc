#include <iostream>
#include <cstdlib>

int data;

typedef struct
{
    int data;
} ExportData;

int (*getValue_function)();

extern "C" {
    typedef void (*foo_function)();

    const char *getModuleName()
    {
        return "Test Module";
    }

    void onModuleLoad(void *initialData)
    {
        if (initialData != NULL)
        {
            ExportData *import = (ExportData *)initialData;
            data = import->data;
        }
        else
        {
            data = 10;
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
        std::cout << "hello from lib replacement: " << data << std::endl;
    }
}
