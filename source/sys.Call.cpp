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

api::System& Call::get() noexcept
{
    return System::getSystem();
}

} // namespace sys
} // namespace eoos
