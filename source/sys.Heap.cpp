/**
 * The operating system heap memory.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018-2020, Sergey Baigudin, Baigudin Software
 */
#include "sys.Heap.hpp"
#include "sys.Allocator.hpp"

namespace eoos
{
    namespace sys
    {
        /**
         * Constructor.
         */
        Heap::Heap() : Parent()
        {
        }

        /**
         * Destructor.
         */
        Heap::~Heap()
        {
        }

        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */
        bool_t Heap::isConstructed() const
        {
            return Parent::isConstructed();
        }

        /**
         * Allocates memory.
         *
         * @param size - required memory size in byte.
         * @param ptr  - NULLPTR value becomes to allocate memory, and
         *               other given values are simply returned
         *               as memory address.
         * @return pointer to allocated memory or NULLPTR.
         */
        void* Heap::allocate(size_t const size, void* const ptr)
        {
            void* addr;
            if(ptr == NULLPTR)
            {
                addr = Allocator::allocate(size);
            }
            else
            {
                addr = ptr;
            }
            return addr;
        }

        /**
         * Frees an allocated memory.
         *
         * @param ptr - pointer to allocated memory.
         */
        void Heap::free(void* const ptr)
        {
            Allocator::free(ptr);
        }
    }
}
