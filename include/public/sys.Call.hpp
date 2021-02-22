/**
 * @brief System calls of the operating system.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_CALL_HPP_
#define SYS_CALL_HPP_

#include "api.System.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @brief System calls class of the operating system.
 */
class Call
{

public:

    /**
     * @brief Returns the operating system syscall interface.
     *
     * @return the operating system syscall interface.
     */
    static api::System& get();

};

} // namespace sys
} // namespace eoos
#endif // SYS_CALL_HPP_
