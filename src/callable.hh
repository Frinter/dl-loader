#pragma once

class Callable
{
public:
    virtual void *call(void *arguments) = 0;
};
