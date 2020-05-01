/**
 * Thread class of this scheduler.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2018, Sergey Baigudin, Baigudin Software
 * @license   http://embedded.team/license/
 */
#ifndef SYS_SCHEDULER_THREAD_HPP_
#define SYS_SCHEDULER_THREAD_HPP_

#include "sys.Object.hpp"
#include "api.Thread.hpp"
#include "api.Task.hpp"
#include "sys.Semaphore.hpp"
#include "sys.Interrupt.hpp"

namespace eoos
{
    namespace sys
    {
        class SchedulerThread : public Object, public api::Thread
        {
            typedef SchedulerThread        Self;
            typedef ::eoos::sys::Object Parent;

        public:

            /**
             * Constructor of not constructed object.
             *
             * @param task a task interface whose main method is invoked when this thread is started.
             */
            SchedulerThread(api::Task& task, Scheduler* scheduler) : Parent(),
                sem_           (0),
                task_          (&task),
                scheduler_     (scheduler),
                id_            (-1),
                res_           (-1),
                status_        (NEW),
                this_          (this){
                setConstructed( construct() );
            }

            /**
             * Destructor.
             */
            virtual ~SchedulerThread()
            {
                scheduler_->removeThread(this);
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
             * Causes this thread to begin execution.
             */
            virtual void execute()
            {
                if( not Self::isConstructed() ) return;
                if( status_ != NEW ) return;
                bool_t is = Interrupt::disableAll();
                scheduler_->addThread(this);
                status_ = RUNNABLE;
                Interrupt::enableAll(is);
                sem_.release();
            }

            /**
             * Waits for this thread to die.
             */
            virtual void join()
            {
                if( not Self::isConstructed() ) return;
                // TODO: prc_join(res_);
            }

            /**
             * Causes this thread to sleep.
             *
             * @param millis a time to sleep in milliseconds.
             * @param nanos  an additional nanoseconds to sleep.
             */
            virtual void sleep(int64_t millis, int32_t nanos)
            {
                if( not Self::isConstructed() ) return;
                if(millis == 0)
                {
                    // int32_t micros = nanos / 1000;
                    // The sleep_u OS call does not cause switching threads
                    // and uses all system time quant. Therefore, use the call
                    // only for nanosecond requests

                    // TODO: sleep_u( static_cast<uint32_t>(micros) );
                }
                else
                {
                    // TODO: sleep_m( static_cast<uint32_t>(millis) );
                }
            }

            /**
             * Blocks this thread on given resource and yields the task.
             *
             * @param res a resource.
             */
            virtual void block(api::Resource& res)
            {
                if( not Self::isConstructed() ) return;
            }

            /**
             * Returns the identifier of this thread.
             *
             * @return the thread identifier, or -1 if an error has been occurred.
             */
            virtual int64_t getId() const
            {
                return id_;
            }

            /**
             * Returns this thread priority.
             *
             * @return priority value, or -1 if an error has been occurred.
             */
            virtual int32_t getPriority() const
            {
                return NORM_PRIORITY;
            }

            /**
             * Sets this thread priority.
             *
             * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY], or LOCK_PRIORITY.
             */
            virtual void setPriority(int32_t priority)
            {
            }

            /**
             * Returns a status of this thread.
             *
             * @return this thread status.
             */
            virtual Status getStatus() const
            {
                return Self::isConstructed() ? status_ : DEAD;
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
                if( not task_->isConstructed() ) return false;
                if( not sem_.isConstructed() ) return false;
                /* TODO:
                // Create new thread of the porting OS
                s_prc_attr attr;
                // Set size of thread stack
                attr.stack = task_->getStackSize();
                // Set default OS heap
                attr.heap = 0x100;
                // Set default priority for this thread
                attr.priority = 0;
                // Set default address of .bss section
                attr.bss = 0;
                // Set no exit vector
                attr.exit_vector = NULLPTR;
                res_ = prc_create(&run, &this_, sizeof(SchedulerThread*), &attr);
                id_ = static_cast<int64_t>(res_);
                return id_ >= 0 ? true : false;
                */
                return false;
            }

            /**
             * Runs a method of Runnable interface start vector.
             */
            int32_t run()
            {
                // Wait for calling start method
                sem_.acquire();
                // Call user main method
                int32_t const error = task_->start();
                // Kill the thread
                bool_t is = Interrupt::disableAll();
                status_ = DEAD;
                scheduler_->removeThread(this);
                Interrupt::enableAll(is);
                return static_cast<int>(error);
            }

            /**
             * Runs a method of Runnable interface start vector.
             */
            static int run(void* argument)
            {
                if(argument == NULLPTR) return -1;
                SchedulerThread* thread = *reinterpret_cast<SchedulerThread**>(argument);
                if(thread == NULLPTR || not thread->isConstructed() ) return -1;
                // Invoke the member function through the pointer
                return thread->run();
            }

            /**
             * Copy constructor.
             *
             * @param obj reference to source object.
             */
            SchedulerThread(const SchedulerThread& obj);

            /**
             * Assignment operator.
             *
             * @param obj reference to source object.
             * @return reference to this object.
             */
            SchedulerThread& operator =(const SchedulerThread& obj);

            /**
             * The semaphore gives the started thread main method to start user task main method.
             */
            Semaphore sem_;

            /**
             * User executing runnable interface.
             */
            api::Task* task_;

            /**
             * The scheduler resource.
             */
            Scheduler* scheduler_;

            /**
             * Current identifier.
             */
            int64_t id_;

            /**
             * Current identifier is a resource of porting OS process.
             */
            int32_t res_;

            /**
             * Current status.
             */
            Status status_;

            /**
             * This class pointer.
             */
            SchedulerThread* this_;

        };
    }
}
#endif // SYS_SCHEDULER_THREAD_HPP_
