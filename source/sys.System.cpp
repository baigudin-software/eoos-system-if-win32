/**
 * @file      sys.System.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2022, Sergey Baigudin, Baigudin Software
 */
#include "sys.System.hpp"
#include "sys.Mutex.hpp"
#include "sys.Semaphore.hpp"
#include "Program.hpp"
#include "lib.LinkedList.hpp"
#include "lib.UniquePointer.hpp"

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
    cout_.flush();
    cerr_.flush();
    eoos_ = NULLPTR;
}

bool_t System::isConstructed() const
{
    return Parent::isConstructed();
}

api::Scheduler& System::getScheduler()
{
    if( !isConstructed() )
    {
        exit(Error::SYSCALL_CALLED);
    }
    return scheduler_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}

api::Heap& System::getHeap()
{
    if( !isConstructed() )
    {
        exit(Error::SYSCALL_CALLED);
    }
    return heap_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}

api::OutStream<char_t>& System::getOutStreamChar()
{
    if( !isConstructed() )
    {
        exit(Error::SYSCALL_CALLED);
    }
    return cout_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}

api::OutStream<char_t>& System::getErrorStreamChar()
{
    if( !isConstructed() )
    {
        exit(Error::SYSCALL_CALLED);
    }
    return cerr_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}

api::Mutex* System::createMutex() try
{
    if( !isConstructed() )
    {
        return NULLPTR;
    }    
    lib::UniquePointer<api::Mutex> res{ new Mutex() }; ///< SCA AUTOSAR-C++14 Justified Rule A18-5-2
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

api::Semaphore* System::createSemaphore(int32_t permits) try
{
    if( !isConstructed() )
    {
        return NULLPTR;
    }
    lib::UniquePointer<api::Semaphore> res{ new Semaphore(permits) }; ///< SCA AUTOSAR-C++14 Justified Rule A18-5-2
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
            if(argv[i] == NULLPTR)
            {
                error = static_cast<int32_t>(Error::ARGUMENT);
                break;
            }
            args.add(argv[i]);
        }
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
    {
        exit(Error::SYSCALL_CALLED);
    }
    return *eoos_;
}

void System::exit(Error const error)
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
        {
            break;
        }
        if( eoos_ != NULLPTR )
        {
            break;
        }        
        if( !scheduler_.isConstructed() )
        {
            break;
        }
        if( !heap_.isConstructed() )
        {
            break;
        }
        if( !cout_.isConstructed() )
        {
            break;
        }
        if( !cerr_.isConstructed() )
        {
            break;
        }
        eoos_ = this;
        res = true;
        break;
    }
    return res;
}

} // namespace sys
} // namespace eoos
