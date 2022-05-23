/**
 * @file      sys.Call.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2022, Sergey Baigudin, Baigudin Software
 */
#include "sys.Call.hpp"
#include "sys.System.hpp"

namespace eoos
{
namespace sys
{

static System* system_{ NULLPTR };

bool_t Call::initialize()
{
    bool_t isConstructed{ false };
    while(true)
    {
        if(system_ != NULLPTR)
        {
            break;
        }
        system_ = new System(); ///< SCA AUTOSAR-C++14 Justified Rule A18-5-2
        if(system_ == NULLPTR)
        {
            break;
        }
        isConstructed = system_->isConstructed();
        if( !isConstructed )
        {
            delete system_; ///< SCA AUTOSAR-C++14 Justified Rule A18-5-2
            system_ = NULLPTR;
        }
        break;
    }
    return isConstructed;
}

void Call::deinitialize()
{
    if(system_ != NULLPTR)
    {
        delete system_; ///< SCA AUTOSAR-C++14 Justified Rule A18-5-2
        system_ = NULLPTR;
    }    
}

int32_t Call::execute()
{
    return (system_ != NULLPTR) ? system_->execute() : -1;
}
    
api::System& Call::get()
{
    if(system_ == NULLPTR)
    {
        System::exit(Error::SYSTEM_ABORT);
    }
    return *system_;
}

} // namespace sys
} // namespace eoos
