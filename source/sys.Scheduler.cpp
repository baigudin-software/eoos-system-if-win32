/**
 * @brief Thread tasks scheduler.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2021, Sergey Baigudin, Baigudin Software
 */
#include "sys.Scheduler.hpp"
#include "sys.Thread.hpp"

namespace eoos
{
namespace sys
{
    
Scheduler::Scheduler() : Parent()
{
    bool_t const isConstructed = construct();
    setConstructed( isConstructed );
}

Scheduler::~Scheduler()
{
}

bool_t Scheduler::isConstructed() const
{
    return Parent::isConstructed();
}

api::Thread* Scheduler::createThread(api::Task& task)
{
    return new Thread {task, this};
}

api::Thread& Scheduler::getCurrentThread() const
{
    api::Thread* tmp;
    return *tmp;
}

void Scheduler::sleepCurrentThread(int64_t millis, int32_t nanos)
{
    ::Sleep( static_cast< ::DWORD >(millis) );
}

void Scheduler::yield()
{
}

api::Toggle& Scheduler::toggle()
{
    return globalThread_;
}

bool_t Scheduler::construct()
{
    bool_t res {false};
    do
    {
        if( not Self::isConstructed() )
        {
            break;
        }
        if( not globalThread_.isConstructed() )
        {
            break;
        }
        res = true;
    } while(false);
    return res;
}

} // namespace sys
} // namespace eoos
