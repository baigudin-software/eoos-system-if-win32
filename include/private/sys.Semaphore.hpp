/**
 * Semaphore class.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHORE_HPP_
#define SYS_SEMAPHORE_HPP_

#include "sys.Object.hpp"
#include "api.Semaphore.hpp"
#include "sys.Interrupt.hpp"

namespace eoos
{
    namespace sys
    {
        class Semaphore : public Object, public api::Semaphore
        {
            typedef Semaphore Self;
            typedef ::eoos::sys::Object Parent;

        public:

            /**
             * Constructor.
             *
             * @param permits the initial number of permits available.
             */
            Semaphore(int32_t permits) : Parent()
            {
                bool_t const isConstructed = construct(permits);
                setConstructed( isConstructed );
            }

            /**
             * Destructor.
             */
            virtual ~Semaphore()
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
             * Acquires one permit from this semaphore.
             *
             * @return true if the semaphore is acquired successfully.
             */
            virtual bool_t acquire()
            {
                if( not Self::isConstructed() ) return false;
                return false;
            }

            /**
             * Acquires the given number of permits from this semaphore.
             *
             * @param permits the number of permits to acquire.
             * @return true if the semaphore is acquired successfully.
             */
            virtual bool_t acquire(int32_t permits)
            {
                if( not Self::isConstructed() ) return false;
                return false;
            }

            /**
             * Releases one permit.
             */
            virtual void release()
            {
                if( not Self::isConstructed() ) return;
            }

            /**
             * Releases the given number of permits.
             *
             * @param permits the number of permits to release.
             */
            virtual void release(int32_t permits)
            {
                if( not Self::isConstructed() ) return;
            }

            /**
             * Tests if this semaphore is fair.
             *
             * @return true if this semaphore has fairness set true.
             */
            virtual bool_t isFair() const
            {
                return false;
            }

            /**
             * Tests if this resource is blocked.
             *
             * @return true if this resource is blocked.
             */
            virtual bool_t isBlocked() const
            {
                if( not Self::isConstructed() ) return false;
                return false;
            }

        private:

            /**
             * Constructor.
             *
             * @param permits the initial number of permits available.
             * @return true if object has been constructed successfully.
             */
            bool_t construct(int32_t permits)
            {
                if( not Self::isConstructed() ) return false;
                return true;
            }

            /**
             * Copy constructor.
             *
             * @param obj reference to source object.
             */
            Semaphore(const Semaphore& obj);

            /**
             * Assignment operator.
             *
             * @param obj reference to source object.
             * @return reference to this object.
             */
            Semaphore& operator =(const Semaphore& obj);

        };
    }
}
#endif // SYS_SEMAPHORE_HPP_