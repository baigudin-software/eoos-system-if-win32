/**
 * @file      sys.SemaphoreManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.SemaphoreManager.hpp"
#include "sys.Semaphore.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

SemaphoreManager::SemaphoreManager() noexcept 
    : NonCopyable<NoAllocator>()
    , api::SemaphoreManager() {
    setConstructed( true );
}

bool_t SemaphoreManager::isConstructed() const noexcept
{
    return Parent::isConstructed();
}    

api::Semaphore* SemaphoreManager::create(int32_t permits) noexcept try
{
    lib::UniquePointer<api::Semaphore> res;
    if( isConstructed() )
    {
        res.reset( new Semaphore<Allocator>(permits) ); ///< SCA AUTOSAR-C++14 Justified Rule A18-5-2
        if( !res.isNull() )
        {   ///< UT Justified Branch: HW dependency
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

} // namespace sys
} // namespace eoos
