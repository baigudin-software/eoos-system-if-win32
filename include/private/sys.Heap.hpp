/**
 * The operating system heap memory.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018-2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_HEAP_HPP_
#define SYS_HEAP_HPP_

#include "sys.Object.hpp"
#include "api.Heap.hpp"

namespace eoos
{
    namespace sys
    {
        class Heap : public Object, public api::Heap
        {
            typedef Heap Self;
            typedef sys::Object Parent;

        public:

            /**
             * Constructor.
             */
            Heap();

            /**
             * Destructor.
             */
            virtual ~Heap();

            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */
            virtual bool_t isConstructed() const;

            /**
             * Allocates memory.
             *
             * @param size - required memory size in byte.
             * @param ptr  - NULLPTR value becomes to allocate memory, and
             *               other given values are simply returned
             *               as memory address.
             * @return pointer to allocated memory or NULLPTR.
             */
            virtual void* allocate(size_t size, void* ptr);

            /**
             * Frees an allocated memory.
             *
             * @param ptr - pointer to allocated memory.
             */
            virtual void free(void* ptr);

        };
    }
}
#endif // SYS_HEAP_HPP_
