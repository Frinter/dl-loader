#include "util/repository.hh"

void *Repository::get(const std::string &key)
{
    if (_registry.find(key) == _registry.end())
        return NULL;

    return _registry[key];
}

void Repository::save(const std::string &key, void *value)
{
    _registry[key] = value;
}

void Repository::remove(const std::string &key)
{
    std::map<std::string, void *>::iterator location = _registry.find(key);

    if (location != _registry.end())
        _registry.erase(location);
}
