#pragma once

#include "moduleinterfacerepository.hh"

typedef struct {
    void *initialData;
    ModuleInterfaceRepository *modules;
} LoadParameters;
