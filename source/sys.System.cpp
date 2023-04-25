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

System::System() 
    : NonCopyable()
    , api::System() {
    bool_t const isConstructed{ construct() };
    setConstructed( isConstructed );
}

System::~System()
{
    eoos_ = NULLPTR;
}

bool_t System::isConstructed() const
{
    return Parent::isConstructed();
}

api::Heap& System::getHeap()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(Error::SYSCALL_CALLED);
    }
    return heap_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}

api::Scheduler& System::getScheduler()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(Error::SYSCALL_CALLED);
    }
    return scheduler_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}

bool_t System::hasMutexManager()
{
    bool_t res{ true };
    if( !isConstructed() )
    {
        res = false;
    }
    return res;
}

api::MutexManager& System::getMutexManager()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(Error::SYSCALL_CALLED);
    }
    return mutex_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}

bool_t System::hasSemaphoreManager()
{
    bool_t res{ true };
    if( !isConstructed() )
    {
        res = false;
    }
    return res;
}

api::SemaphoreManager& System::getSemaphoreManager()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(Error::SYSCALL_CALLED);
    }
    return semaphore_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}

bool_t System::hasStreamManager()
{
    bool_t res{ true };
    if( !isConstructed() )
    {
        res = false;
    }
    return res;
}

api::StreamManager& System::getStreamManager()
{
    if( !isConstructed() )
    {   ///< UT Justified Branch: HW dependency
        exit(Error::SYSCALL_CALLED);
    }
    return stream_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1    
}

int32_t System::execute() const ///< SCA AUTOSAR-C++14 Justified Rule M9-3-3
{
    char_t* args[]{ NULLPTR };
    return execute(0, args); ///< SCA AUTOSAR-C++14 Justified Rule A5-2-12
}

int32_t System::execute(int32_t argc, char_t* argv[]) const ///< SCA AUTOSAR-C++14 Justified Rule A8-4-8
{
    int32_t error( static_cast<int32_t>(Error::OK) );
    if( isConstructed() && (argc >= 0) && (argv != NULLPTR) )
    {
        lib::LinkedList<char_t*> args;
        for(int32_t i(0); i<argc; i++)
        {
            if( argv[i] != NULLPTR )
            {
                if( args.add(argv[i]) )
                {
                    continue;
                }
            }
            error = static_cast<int32_t>(Error::ARGUMENT);
            break;
        } ///< UT Justified Line: Compiler dependency
        if( (error != static_cast<int32_t>(Error::ARGUMENT) ) && (argv[argc] != NULLPTR) )
        {
            error = static_cast<int32_t>(Error::ARGUMENT);
        }
        if( error != static_cast<int32_t>(Error::ARGUMENT) )
        {
            error = Program::start(args);
        }
    }
    else
    {
        error = static_cast<int32_t>(Error::ARGUMENT);
    }
    return error;
}

api::System& System::getSystem()
{
    if(eoos_ == NULLPTR)
    {   ///< UT Justified Branch: Startup dependency
        exit(Error::SYSCALL_CALLED);
    }
    return *eoos_;
}

void System::exit(Error const error) ///< UT Justified Branch: OS dependency
{
    ::ExitProcess(static_cast< ::UINT >(error));
    // This code must NOT be executed
    // @todo throw an exection here is better.
    while( true ){}
}

bool_t System::construct()
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

} // namespace sys
} // namespace eoos
