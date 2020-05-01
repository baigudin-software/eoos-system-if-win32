/**
 * Mutex class.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_MUTEX_HPP_
#define SYS_MUTEX_HPP_

#include "sys.Object.hpp"
#include "api.Mutex.hpp"

namespace eoos
{
    namespace sys
    {
        class Mutex : public Object, public api::Mutex
        {
                typedef Mutex Self;
                typedef ::eoos::sys::Object Parent;

        public:

            /**
             * Constructor.
             */
            Mutex() : Parent()
            {
                bool_t const isConstructed = construct();
                setConstructed( isConstructed );
            }

            /**
             * Destructor.
             */
            virtual ~Mutex()
            {
            }

            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */
            virtual bool_t isConstructed() const
            {
                return Parent::isConstructed();
            }


            /**
             * Locks the mutex.
             *
             * @return true if the mutex is lock successfully.
             */
            virtual bool_t lock()
            {
                if( not Self::isConstructed() ) return false;
                return false;
            }

            /**
             * Unlocks the mutex.
             */
            virtual void unlock()
            {
                if( not Self::isConstructed() ) return;
            }

            /**
             * Tests if this resource is blocked.
             *
             * @return true if this resource is blocked.
             */
            virtual bool_t isBlocked()const
            {
                if( not Self::isConstructed() ) return false;
                return false;
            }

        private:

            /**
             * Constructor.
             *
             * @return true if object has been constructed successfully.
             */
            bool_t construct()
            {
                if( not Self::isConstructed() ) return false;
                return true;
            }

            /**
             * Copy constructor.
             *
             * @param obj reference to source object.
             */
            Mutex(const Mutex& obj);

            /**
             * Assignment operator.
             *
             * @param obj reference to source object.
             * @return reference to this object.
             */
            Mutex& operator =(const Mutex& obj);

        };
    }
}
#endif // SYS_MUTEX_HPP_
