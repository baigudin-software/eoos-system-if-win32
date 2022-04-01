/**
 * @file      sys.Scheduler.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2022, Sergey Baigudin, Baigudin Software
 */
#include "sys.Scheduler.hpp"
#include "sys.Thread.hpp"

namespace eoos
{
namespace sys
{
    
Scheduler::Scheduler() try : Parent()
{
    bool_t const isConstructed = construct();
    setConstructed( isConstructed );
} catch (...) {
    setConstructed(false);
}

Scheduler::~Scheduler()
{
}

bool_t Scheduler::isConstructed() const
{
    return Parent::isConstructed();
}

api::Thread* Scheduler::createThread(api::Task& task) try
{
    return new Thread {task};
} catch (...) {
    return NULLPTR;
}

bool_t Scheduler::sleep(int32_t ms) try
{
    ::Sleep( static_cast< ::DWORD >(ms) );
    return true;
} catch (...) {
    return false;
}

void Scheduler::yield() try
{
    ::Sleep(0);
} catch (...) {
    return;
}

bool_t Scheduler::construct()
{
    bool_t res {false};
    do
    {
        if( not isConstructed() )
        {
            break;
        }
        processHandle_ = ::GetCurrentProcess();
        if(processHandle_ == NULLPTR)
        {
            break;
        }
        processPriority_ = ::GetPriorityClass(processHandle_);
        if(processPriority_ == 0)
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

} // namespace sys
} // namespace eoos
