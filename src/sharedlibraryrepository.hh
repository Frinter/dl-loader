#pragma once

#include <map>
#include <string>

#include "sharedlibrary.hh"

class SharedLibraryRepository
{
public:
    void registerLibrary(const std::string &path, SharedLibrary *library);
    void unregisterLibrary(const std::string &path);

    SharedLibrary *get(const std::string &path);

private:
    std::map<std::string, SharedLibrary *> _registry;
};
