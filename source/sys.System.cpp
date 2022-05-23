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
        
bool_t System::isInitialized_{ false };

System::System() 
    : NonCopyable()
    , api::System() {
    bool_t const isConstructed{ construct() };
    setConstructed( isConstructed );
}

System::~System()
{
    isInitialized_ = false;
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
    int32_t error;
    if( !isConstructed() )
    {
        error = static_cast<int32_t>(Error::UNDEFINED);
    }
    else
    {
        lib::LinkedList<char_t*> args;
        error = Program::start(&args);
    }
    return error;
}

void System::exit(Error const error)
{
    ::ExitProcess(static_cast< ::UINT >(error));
    // This code must NOT be executed
    // @todo throw an exection here is better.
    while( true ){}
}

bool_t System::construct() const
{
    bool_t res{ isConstructed() };
    while(res == true)
    {
        if( isInitialized_ )
        {
            res = false;
            continue;
        }
        if( !scheduler_.isConstructed() )
        {
            res = false;
            continue;
        }
        isInitialized_ = true;
        break;
    }
    return res;
}

} // namespace sys
} // namespace eoos
