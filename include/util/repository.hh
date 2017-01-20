#pragma once

#include <map>
#include <string>

class Repository
{
public:
    void *get(const std::string &key);

    void save(const std::string &key, void *value);
    void remove(const std::string &key);

private:
    std::map<std::string, void *> _registry;
};
