#include "module.hh"
#include "moduleinterfacerepository.hh"

#include "modulerepository.hh"

void ModuleRepository::save(const std::string &key, Module *module)
{
    if (_modules.get(key) != NULL)
    {
        std::string message = "Attempting to add duplicate entry for module: ";
        message += key;
        throw std::logic_error(message);
    }

    _modules.save(key, (void *)module);
}

void ModuleRepository::remove(const std::string &key)
{
    _modules.remove(key);
}

Module *ModuleRepository::get(const std::string &key)
{
    return (Module *)_modules.get(key);
}

ModuleFunctionLoader *ModuleRepository::getModuleInterface(const std::string &name)
{
    return (ModuleFunctionLoader *)_modules.get(name);
}
