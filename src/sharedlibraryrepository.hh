#pragma once

#include <map>
#include <string>

#include "util/repository.hh"
#include "sharedlibrary.hh"

class SharedLibraryRepository
{
public:
    void save(const std::string &path, SharedLibrary *library);
    void remove(const std::string &path);

    SharedLibrary *get(const std::string &path);

private:
    Repository _registry;
};
