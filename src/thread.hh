#pragma once

#include "command.hh"

class Thread
{
public:
    static Thread *create(Command *command);

public:
    virtual ~Thread() {}

    virtual void join() = 0;

protected:
    Thread() {}

private:
    Thread(Command *command) {}
    Thread(const Thread &o) = delete;
};
