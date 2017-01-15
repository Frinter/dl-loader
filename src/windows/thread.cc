#include <windows.h>

#include "thread.hh"

namespace Windows {
    class Thread : public ::Thread
    {
    public:
        Thread(Command *command)
            : _command(command)
        {
            _threadHandle = CreateThread(NULL, 0, Thread::startThread, this, 0, NULL);
        }

        ~Thread()
        {
        }

        void join() {
            WaitForSingleObject(_threadHandle, INFINITE);
        }

        void start() {
            _command->execute();
        }

    private:
        Command *_command;
        HANDLE _threadHandle;

    private:
        static DWORD WINAPI startThread(LPVOID args)
        {
            Thread *self = (Thread *)args;
            self->start();
            return NULL;
        }
    };
}

Thread *Thread::create(Command *command)
{
    return new Windows::Thread(command);
}
