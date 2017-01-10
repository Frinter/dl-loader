#include <iostream>
#include <cstdlib>

extern "C" {
    void onModuleLoad(void *initialData)
    {
    }

    void *exportModuleData()
    {
        return NULL;
    }

    void *getValue(void *arguments)
    {
        std::cout << "in dependency" << std::endl;
        return new int(10);
    }
}
