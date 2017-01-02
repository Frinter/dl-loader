#include <stdexcept>
#include <cstdlib>

#include "sharedlibraryrepository.hh"

void SharedLibraryRepository::save(const std::string &path, SharedLibrary *library)
{
    if (_registry.get(path) != NULL)
    {
        std::string message = "Duplicate entry for shared library: ";
        message += path;
        throw std::logic_error(message);
    }

    _registry.save(path, (void *)library);
}

void SharedLibraryRepository::remove(const std::string &path)
{
    _registry.remove(path);
}

SharedLibrary *SharedLibraryRepository::get(const std::string &path)
{
    return (SharedLibrary *)_registry.get(path);
}
