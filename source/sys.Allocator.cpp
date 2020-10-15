/**
 * The operating system memory allocator.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2020, Sergey Baigudin, Baigudin Software
 */
#include "sys.Allocator.hpp"

namespace eoos
{
    namespace sys
    {
        void* Allocator::allocate(size_t const size)
        {
            return new cell_t[size];
        }

        void Allocator::free(void* const ptr)
        {
            delete[] ptr;
        }
    }
}
