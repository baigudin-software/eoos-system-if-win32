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
    lib::UniquePointer<Thread> res;
    if( isConstructed() )
    {
        res.reset( new Thread(task) ); ///< SCA AUTOSAR-C++14 Justified Rule A18-5-2
        if( !res.isNull() )
        {
            if( !res->isConstructed() )
            {
                res.reset();
            }
        }
    }
    return res.release();
} catch (...) { ///< UT Justified Branch: OS dependency
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
} catch (...) { ///< UT Justified Branch: OS dependency
    return false;
}

void Scheduler::yield() try
{
    ::Sleep(0U);
} catch (...) { ///< UT Justified Branch: OS dependency
    return;
}

bool_t Scheduler::construct() try
{
    bool_t res{ false };
    while(true)
    {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        processHandle_ = ::GetCurrentProcess();
        if(processHandle_ == NULLPTR)
        {   ///< UT Justified Branch: OS dependency
            break;
        }
        processPriority_ = ::GetPriorityClass(processHandle_);
        if(processPriority_ == 0U)
        {   ///< UT Justified Branch: OS dependency
            break;
        }
        res = true;
        break;
    }
    return res;
} catch (...) { ///< UT Justified Branch: OS dependency
    return false;
}

} // namespace sys
} // namespace eoos
