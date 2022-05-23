/**
 * @file      sys.Scheduler.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2022, Sergey Baigudin, Baigudin Software
 */
#include "sys.Scheduler.hpp"
#include "sys.Thread.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{
    
Scheduler::Scheduler()
    : NonCopyable()
    , api::Scheduler() {
    bool_t const isConstructed{ construct() };
    setConstructed( isConstructed );
}

bool_t Scheduler::isConstructed() const
{
    return Parent::isConstructed();
}

api::Thread* Scheduler::createThread(api::Task& task) try ///< SCA AUTOSAR-C++14 Justified Rule A8-4-8
{
    if( !isConstructed() )
    {
        return NULLPTR;
    }    
    lib::UniquePointer<Thread> res{ new Thread(task) }; ///< SCA AUTOSAR-C++14 Justified Rule A18-5-2
    if( !res.isNull() )
    {
        if( !res->isConstructed() )
        {
            res.reset();
        }
    }
    return res.release();
} catch (...) {
    return NULLPTR;
}

bool_t Scheduler::sleep(int32_t ms) try
{
    bool_t res{ false };
    if(ms >= 0)
    {    
        ::Sleep( static_cast< ::DWORD >(ms) );
        res = true;
    }
    return res;
} catch (...) {
    return false;
}

void Scheduler::yield() try
{
    ::Sleep(0U);
} catch (...) {
    return;
}

bool_t Scheduler::construct() try
{
    bool_t res{ false };
    while(true)
    {
        if( !isConstructed() )
        {
            break;
        }
        processHandle_ = ::GetCurrentProcess();
        if(processHandle_ == NULLPTR)
        {
            break;
        }
        processPriority_ = ::GetPriorityClass(processHandle_);
        if(processPriority_ == 0U)
        {
            break;
        }
        res = true;
        break;
    }
    return res;
} catch (...) {
    return false;
}

} // namespace sys
} // namespace eoos
