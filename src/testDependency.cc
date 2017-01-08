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

    int getValue()
    {
        std::cout << "in dependency" << std::endl;
        return 10;
    }
}
