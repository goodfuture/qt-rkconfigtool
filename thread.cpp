#include "thread.h"

Thread::Thread(QObject *parent) :
    QThread(parent)
{
}

Thread::~Thread()
{
    exit(0);
}
