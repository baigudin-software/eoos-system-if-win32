/**
 * @file      sys.StreamManager.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.StreamManager.hpp"

namespace eoos
{
namespace sys
{

StreamManager::StreamManager() noexcept 
    : NonCopyable<NoAllocator>()
    , api::StreamManager() {
    setConstructed( true );
}

StreamManager::~StreamManager() noexcept
{
    cout_.flush();
    cerr_.flush();        
}

bool_t StreamManager::isConstructed() const noexcept
{
    return Parent::isConstructed();
}

api::OutStream<char_t>& StreamManager::getCout() noexcept
{
    return cout_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}

api::OutStream<char_t>& StreamManager::getCerr() noexcept
{
    return cerr_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
}    

} // namespace sys
} // namespace eoos
