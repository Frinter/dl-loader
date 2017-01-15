#include "readwritelock.hh"

ReadWriteLock::ReadWriteLock()
    : _currentReaders(0)
{
    _readerLock = Mutex::create();
    _writerLock = Mutex::create();
}

ReadWriteLock::~ReadWriteLock()
{
    delete _readerLock;
    delete _writerLock;
}

void ReadWriteLock::beginRead()
{
    _readerLock->lock();

    _currentReaders += 1;
    if (_currentReaders == 1)
        _writerLock->lock();

    _readerLock->unlock();
}

void ReadWriteLock::endRead()
{
    _readerLock->lock();

    _currentReaders -= 1;
    if (_currentReaders == 0)
        _writerLock->unlock();

    _readerLock->unlock();
}

void ReadWriteLock::beginWrite()
{
    _writerLock->lock();
}

void ReadWriteLock::endWrite()
{
    _writerLock->unlock();
}
