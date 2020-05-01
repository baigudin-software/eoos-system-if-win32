/**
 * Hardware interrupt resource.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_INTERRUPT_HPP_
#define SYS_INTERRUPT_HPP_

#include "sys.Object.hpp"
#include "api.Interrupt.hpp"
#include "api.Task.hpp"

namespace eoos
{
    namespace sys
    {
        class Interrupt : public Object, public api::Interrupt
        {
            typedef Interrupt Self;
            typedef ::eoos::sys::Object Parent;

        public:

            /**
             * Constructor.
             *
             * @param handler user class which implements an interrupt handler interface.
             * @param source  available interrupt source.
             */
            Interrupt(api::Task& handler, int32_t source);

            /**
             * Destructor.
             */
            virtual ~Interrupt();

            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */
            virtual bool_t isConstructed() const;

            /**
             * Jumps to interrupt hardware vector.
             */
            virtual void jump();

            /**
             * Clears an interrupt status of this source.
             */
            virtual void clear();

            /**
             * Sets an interrupt status of this source.
             */
            virtual void set();

            /**
             * Locks this interrupt source.
             *
             * @return an interrupt enable source bit value before method was called.
             */
            virtual bool_t disable();

            /**
             * Unlocks this interrupt source.
             *
             * @param status returned status by lock method.
             */
            virtual void enable(bool_t status);

            /**
             * Disables all maskable interrupts.
             *
             * @return global interrupts enable bit value before method was called.
             */
            static bool_t disableAll();

            /**
             * Enables all maskable interrupts.
             *
             * The true passed argument directly turns all maskable interrupts on,
             * and the false does nothing, the interrupts stay in the current state.
             *
             * @param status the returned status by disable method.
             */
            static void enableAll(bool_t status=true);

        private:

            /**
             * Constructor.
             *
             * @param handler pointer to user class which implements an interrupt handler interface.
             * @param source  available interrupt source.
             * @return true if object has been constructed successfully.
             */
            bool_t construct(api::Task* handler, int32_t source);

            /**
             * Copy constructor.
             *
             * @param obj reference to source object.
             */
            Interrupt(const Interrupt& obj);

            /**
             * Assignment operator.
             *
             * @param obj reference to source object.
             * @return reference to this object.
             */
            Interrupt& operator =(const Interrupt& obj);

        };
    }
}
#endif // SYS_INTERRUPT_HPP_
