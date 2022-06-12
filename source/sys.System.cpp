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
    return heap_;
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

int32_t System::execute() ///< SCA AUTOSAR-C++14 Justified Rule M9-3-3
{
    return execute(0, NULLPTR);
}

int32_t System::execute(int32_t argc, char_t* argv[])
{
    int32_t error;
    if( !isConstructed() )
    {
        error = static_cast<int32_t>(Error::UNDEFINED);
    }
    else
    {
        lib::LinkedList<char_t*> args;
        for(int32_t i(0); i<argc; i++)
        {
            args.add(argv[i]);
        }
        error = Program::start(args);
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
    bool_t res{ isConstructed() };
    while(res == true)
    {
        if( eoos_ != NULLPTR )
        {
            res = false;
            continue;
        }
        if( !scheduler_.isConstructed() )
        {
            res = false;
            continue;
        }
        if( !heap_.isConstructed() )
        {
            res = false;
            continue;
        }
        eoos_ = this;
        break;
    }
    return res;
}

} // namespace sys
} // namespace eoos
