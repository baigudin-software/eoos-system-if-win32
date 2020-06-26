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
        Heap::Heap() : Parent()
        {
        }

        Heap::~Heap()
        {
        }

        bool_t Heap::isConstructed() const
        {
            return Parent::isConstructed();
        }

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

        void Heap::free(void* const ptr)
        {
            Allocator::free(ptr);
        }
    }
}
