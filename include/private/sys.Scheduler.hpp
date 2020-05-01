/**
 * Thread tasks scheduler.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SCHEDULER_HPP_
#define SYS_SCHEDULER_HPP_

#include "sys.Object.hpp"
#include "api.Scheduler.hpp"
#include "sys.GlobalThread.hpp"
#include "lib.LinkedList.hpp"

namespace eoos
{
    namespace sys
    {
        class SchedulerThread;

        class Scheduler : public Object, public api::Scheduler
        {
            typedef Scheduler Self;
            typedef ::eoos::sys::Object Parent;

        public:

            /**
             * Constructor.
             */
            Scheduler();

            /**
             * Destructor.
             */
            virtual ~Scheduler();

            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */
            virtual bool_t isConstructed() const;

            /**
             * Creates a new thread.
             *
             * @param task an user task which main method will be invoked when created thread is started.
             * @return a new thread.
             */
            virtual api::Thread* createThread(api::Task& task);

            /**
             * Returns currently executing thread.
             *
             * @return executing thread.
             */
            virtual api::Thread& getCurrentThread() const;

            /**
             * Yields to next thread.
             */
            virtual void yield();

            /**
             * Returns the toggle interface for controlling global thread switching.
             *
             * @return toggle interface.
             */
            virtual api::Toggle& toggle();

            /**
             * Adds a thread to execution list
             *
             * @return true if thread has been added successfully.
             */
            bool_t addThread(SchedulerThread* thread);

            /**
             * Removes the first occurrence of the specified thread.
             *
             * @param thread removing thread.
             */
            void removeThread(SchedulerThread* thread);

        private:

            /**
             * Constructor.
             *
             * When first scheduler timer interrupt is occurred,
             * default registers of parent interrupt class will be used
             * for storing the operating system context to it.
             *
             * @return true if object has been constructed successfully.
             */
            bool_t construct();

            /**
             * Copy constructor.
             *
             * @param obj reference to source object.
             */
            Scheduler(const Scheduler& obj);

            /**
             * Assignment operator.
             *
             * @param obj reference to source object.
             * @return reference to this object.
             */
            Scheduler& operator =(const Scheduler& obj);

            /**
             * Global thread switching controller.
             */
            GlobalThread globalThread_;

            /**
             * The tasks list.
             */
            lib::LinkedList< SchedulerThread* > threads_;

        };
    }
}
#endif // SYS_SCHEDULER_HPP_
