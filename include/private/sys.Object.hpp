/**
 * Root class of the operating system class hierarchy.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OBJECT_HPP_
#define SYS_OBJECT_HPP_

#include "Object.hpp"
#include "sys.Allocator.hpp"

namespace eoos
{
    namespace sys
    {
        class Object : public ::eoos::Object<Allocator>
        {
            typedef ::eoos::Object<Allocator> Parent;

        public:

            /**
             * Constructor.
             */
            Object();

            /**
             * Destructor.
             */
            virtual ~Object();

        };
    }
}
#endif // SYS_OBJECT_HPP_
