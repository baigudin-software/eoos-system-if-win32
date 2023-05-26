/**
 * @file      sys.System.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.System.hpp"
#include "Program.hpp"
#include "lib.LinkedList.hpp"

namespace eoos
{
namespace sys
{
        
api::System* System::eoos_{ NULLPTR };

System::System() noexcept
    : NonCopyable<NoAllocator>()
    , api::System() {
    bool_t const isConstructed{ construct() };
    setConstructed( isConstructed );
}

System::~System() noexcept
{
    eoos_ = NULLPTR;
}

bool_t System::isConstructed() const noexcept
{
    return Parent::isConstructed();
}

api::Heap& System::getHeap() noexcept
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(Error::SYSCALL_CALLED);
    }
    return heap_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}

api::Scheduler& System::getScheduler() noexcept
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(Error::SYSCALL_CALLED);
    }
    return scheduler_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}

bool_t System::hasMutexManager() noexcept
{
    bool_t res{ true };
    if( !isConstructed() )
    {
        res = false;
    }
    return res;
}

api::MutexManager& System::getMutexManager() noexcept
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(Error::SYSCALL_CALLED);
    }
    return mutex_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}

bool_t System::hasSemaphoreManager() noexcept
{
    bool_t res{ true };
    if( !isConstructed() )
    {
        res = false;
    }
    return res;
}

api::SemaphoreManager& System::getSemaphoreManager() noexcept
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(Error::SYSCALL_CALLED);
    }
    return semaphore_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}

bool_t System::hasStreamManager() noexcept
{
    bool_t res{ true };
    if( !isConstructed() )
    {
        res = false;
    }
    return res;
}

api::StreamManager& System::getStreamManager() noexcept
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(Error::SYSCALL_CALLED);
    }
    return stream_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1    
}

int32_t System::execute() const noexcept ///< SCA AUTOSAR-C++14 Justified Rule M9-3-3
{
    char_t* args[]{ NULLPTR };
    return execute(0, args); ///< SCA AUTOSAR-C++14 Justified Rule A5-2-12
}

int32_t System::execute(int32_t argc, char_t* argv[]) const noexcept ///< SCA AUTOSAR-C++14 Justified Rule A8-4-8
{
    return Program::start(argc, argv);
}

api::System& System::getSystem() noexcept
{
    if(eoos_ == NULLPTR)
    {   ///< UT Justified Branch: Startup dependency
        exit(Error::SYSCALL_CALLED);
    }
    return *eoos_;
}

bool_t System::construct() noexcept
{
    bool_t res( false );
    while(true) 
    {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( eoos_ != NULLPTR )
        {   ///< UT Justified Branch: Startup dependency
            break;
        }        
        if( !scheduler_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !heap_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !mutex_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !semaphore_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        if( !stream_.isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }        
        eoos_ = this;
        res = true;
        break;
    } ///< UT Justified Line: Compiler dependency
    return res;
}

void System::exit(Error const error) ///< UT Justified Branch: OS dependency
{
    ::ExitProcess(static_cast< ::UINT >(error));
    // This code must NOT be executed
    // @todo throw an exection here is better.
    while( true ){}
}

} // namespace sys
} // namespace eoos
