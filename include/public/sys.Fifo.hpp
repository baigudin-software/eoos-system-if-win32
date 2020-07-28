/**
 * Class implements FIFO files.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_FIFO_HPP_
#define SYS_FIFO_HPP_

#ifdef EOOS_WIN32
#include "sys.win32.Fifo.hpp"
#elif EOOS_POSIX
#include "sys.posix.Fifo.hpp"
#else
#error "FIFO is not implemented for OS is used"    
#endif

#if EOOS_CPP_STANDARD < 2011
#error "C++ language standard less than C++11 is not supported"
#endif

namespace eoos
{
    namespace sys
    {
        #ifdef EOOS_WIN32
        using Fifo = win32::Fifo;
        #elif EOOS_POSIX
        using Fifo = posix::Fifo;
        #else
        #error "FIFO is not implemented for OS is used"    
        #endif        
        
    }
}
#endif // SYS_FIFO_HPP_
