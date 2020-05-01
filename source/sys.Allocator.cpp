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
        /**
         * Allocates memory.
         *
         * @param size - number of bytes to allocate.
         * @return allocated memory address or a null pointer.
         */
        void* Allocator::allocate(size_t const size)
        {
            return NULLPTR;
        }

        /**
         * Frees an allocated memory.
         *
         * @param ptr address of allocated memory block or a null pointer.
         */
        void Allocator::free(void* const ptr)
        {
        }

    }
}
