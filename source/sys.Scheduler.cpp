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
    
Scheduler::Scheduler() noexcept
    : NonCopyable<NoAllocator>()
    , api::Scheduler() {
    bool_t const isConstructed{ construct() };
    setConstructed( isConstructed );
}

bool_t Scheduler::isConstructed() const noexcept
{
    return Parent::isConstructed();
}

api::Thread* Scheduler::createThread(api::Task& task) noexcept try ///< SCA AUTOSAR-C++14 Justified Rule A8-4-8
{
    lib::UniquePointer<api::Thread> res;
    if( isConstructed() )
    {
        res.reset( new Thread<Allocator>(task) ); ///< SCA AUTOSAR-C++14 Justified Rule A18-5-2
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

bool_t Scheduler::sleep(int32_t ms) noexcept try
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

bool_t Scheduler::yield() noexcept try
{
    ::Sleep(0U);
    return true;
} catch (...) { ///< UT Justified Branch: OS dependency
    return false;
}

bool_t Scheduler::construct() noexcept try
{
    bool_t res{ false };
    if( isConstructed() )
    {
        processHandle_ = ::GetCurrentProcess();
        if(processHandle_ != NULLPTR)
        {
            processPriority_ = ::GetPriorityClass(processHandle_);
            if(processPriority_ != 0U)
            {
                res = true;
            }
        }
    }
    return res;
} catch (...) { ///< UT Justified Branch: OS dependency
    return false;
}

} // namespace sys
} // namespace eoos
