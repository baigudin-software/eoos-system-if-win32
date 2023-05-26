/**
 * @file      sys.MutexManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.MutexManager.hpp"
#include "sys.Mutex.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

MutexManager::MutexManager() noexcept 
    : NonCopyable<NoAllocator>()
    , api::MutexManager() {
    setConstructed( true );
}

bool_t MutexManager::isConstructed() const noexcept
{
    return Parent::isConstructed();
}    

api::Mutex* MutexManager::create() noexcept try
{
    lib::UniquePointer<api::Mutex> res;
    if( isConstructed() )
    {   
        res.reset( new Mutex<Allocator>() ); ///< SCA AUTOSAR-C++14 Justified Rule A18-5-2
        if( !res.isNull() )
        {
            if( !res->isConstructed() )
            {   ///< UT Justified Branch: HW dependency
                res.reset();
            }
        }
    }
    return res.release();
} catch (...) { ///< UT Justified Branch: OS dependency
    return NULLPTR;
}

void MutexManager::remove(api::Mutex* mutex) noexcept
{
    if( isConstructed() && mutex != NULLPTR )
    {
        delete mutex;
    }
}

} // namespace sys
} // namespace eoos
