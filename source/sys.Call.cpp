/**
 * @brief System calls of the operating system.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2021, Sergey Baigudin, Baigudin Software
 */
#include "sys.Call.hpp"
#include "sys.System.hpp"

namespace eoos
{
namespace sys
{
    
api::System& Call::get()
{
    return System::call();
}

} // namespace sys
} // namespace eoos
