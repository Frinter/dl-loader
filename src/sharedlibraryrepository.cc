#include <stdexcept>
#include <cstdlib>

#include "sharedlibraryrepository.hh"

void SharedLibraryRepository::registerLibrary(const std::string &path, SharedLibrary *library)
{
    if (_registry.find(path) != _registry.end())
    {
        std::string message = "Duplicate entry for shared library: ";
        message += path;
        throw std::logic_error(message);
    }

    _registry[path] = library;
}

void SharedLibraryRepository::unregisterLibrary(const std::string &path)
{
    std::map<std::string, SharedLibrary *>::iterator location = _registry.find(path);

    if (location != _registry.end())
        _registry.erase(location);
}

SharedLibrary *SharedLibraryRepository::get(const std::string &path)
{
    if (_registry.find(path) == _registry.end())
        return NULL;

    return _registry[path];
}
