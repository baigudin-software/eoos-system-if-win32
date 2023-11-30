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
    cout_->flush();
    cerr_->flush();        
}

bool_t StreamManager::isConstructed() const noexcept
{
    return Parent::isConstructed();
}

api::OutStream<char_t>& StreamManager::getCout() noexcept
{
    return *cout_;
}

api::OutStream<char_t>& StreamManager::getCerr() noexcept
{
    return *cerr_;
}

bool_t StreamManager::setCout(api::OutStream<char_t>& cout) noexcept
{
    bool_t res( false );
    if( isConstructed() )
    {
        cout_ = &cout;
        res = true;
    }
    return res;
}

bool_t StreamManager::setCerr(api::OutStream<char_t>& cerr) noexcept
{
    bool_t res( false );
    if( isConstructed() )
    {
        cerr_ = &cerr;
        res = true;
    }
    return res;
}

void StreamManager::resetCout() noexcept
{
    cout_ = &coutDef_;
}

void StreamManager::resetCerr() noexcept
{
    cerr_ = &cerrDef_;
}

} // namespace sys
} // namespace eoos
