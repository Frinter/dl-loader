#pragma once

#include "mutex.hh"

class ReadWriteLock
{
public:
    ReadWriteLock();
    ~ReadWriteLock();

    void beginRead();
    void endRead();

    void beginWrite();
    void endWrite();

private:
    int _currentReaders;
    Mutex *_readerLock;
    Mutex *_writerLock;

private:
    ReadWriteLock(const ReadWriteLock &o) = delete;
};
