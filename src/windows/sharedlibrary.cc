#include <windows.h>
#include <stdexcept>

#include "sharedlibrary.hh"

namespace Windows
{
    std::string getError(DWORD errorId)
    {
        char *buffer;
        size_t size =  FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                      NULL, errorId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char *)&buffer, 0, NULL);
        std::string message(buffer, size);
        LocalFree(buffer);

        return message;
    }


    class SharedLibrary : public ::SharedLibrary
    {
    public:
        SharedLibrary(const char *path)
            : _path(path), _handle(NULL)
        {
        }

        ~SharedLibrary()
        {
        }

        void load()
        {
            _handle = LoadLibrary(_path);
            if (_handle == NULL)
                throw std::runtime_error(std::string(_path) + ": " + getError(GetLastError()));
        }

        void unload()
        {
            if (_handle != NULL)
            {
                FreeLibrary(_handle);
                _handle = NULL;
            }
        }

        void *loadFunction(const char *functionName)
        {
            void *function = (void*)GetProcAddress(_handle, functionName);

            return function;
        }

    private:
        HMODULE _handle;
        const char *_path;
    };
}

SharedLibrary *SharedLibrary::create(const char *path)
{
    return new Windows::SharedLibrary(path);
}
