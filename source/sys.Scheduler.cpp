/**
 * Thread tasks scheduler.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2020, Sergey Baigudin, Baigudin Software
 */
#include "sys.Scheduler.hpp"
#include "sys.SchedulerThread.hpp"
#include "sys.System.hpp"
#include "sys.Interrupt.hpp"

namespace eoos
{
    namespace sys
    {
        /**
         * Constructor.
         */
        Scheduler::Scheduler() : Parent(),
            globalThread_  (),
            threads_       (NULLPTR){
            setConstructed( construct() );
        }

        /**
         * Destructor.
         */
        Scheduler::~Scheduler()
        {
        }

        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */
        bool_t Scheduler::isConstructed() const
        {
            return Parent::isConstructed();
        }

        /**
         * Creates a new thread.
         *
         * @param task an user task which main method will be invoked when created thread is started.
         * @return a new thread.
         */
        api::Thread* Scheduler::createThread(api::Task& task)
        {
            if( not Self::isConstructed() ) return NULLPTR;
            SchedulerThread* thread = new SchedulerThread(task, this);
            if(thread == NULLPTR) return NULLPTR;
            if(thread->isConstructed()) return thread;
            delete thread;
            return NULLPTR;
        }

        /**
         * Returns currently executing thread.
         *
         * @return executing thread.
         */
        api::Thread& Scheduler::getCurrentThread() const
        {
            if( not Self::isConstructed() )
            {
                System::terminate(ERROR_SYSCALL_CALLED);
            }
            bool_t const is = Interrupt::disableAll();
            api::Thread* thread = NULLPTR;
            int64_t id = -1; // TODO: get a current thread ID static_cast<int64_t>( gettid() );
            int32_t length = threads_.getLength();
            for(int32_t i=0; i<length; i++)
            {
                thread = threads_.get(i);
                if(thread == NULLPTR) break;
                if(thread->getId() == id) break;
            }
            if(thread == NULLPTR)
            {
                System::terminate(ERROR_RESOURCE_NOT_FOUND);
            }
            Interrupt::enableAll(is);
            return *thread;
        }

        /**
         * Yields to next thread.
         */
        void Scheduler::yield()
        {
            if( not Self::isConstructed() )
            {
                System::terminate(ERROR_SYSCALL_CALLED);
            }
            // TODO: sched_yield();
        }

        /**
         * Returns the toggle interface for controlling global thread switching.
         *
         * @return toggle interface.
         */
        api::Toggle& Scheduler::toggle()
        {
            return globalThread_;
        }

        /**
         * Constructor.
         *
         * When first scheduler timer interrupt is occurred,
         * default registers of parent interrupt class will be used
         * for storing the operating system context to it.
         *
         * @return true if object has been constructed successfully.
         */
        bool_t Scheduler::construct()
        {
            if( not isConstructed() ) return false;
            if( not globalThread_.isConstructed() ) return false;
            if( not threads_.isConstructed() ) return false;
            return true;
        }

        /**
         * Adds a thread to execution list
         *
         * @return true if thread has been added successfully.
         */
        bool_t Scheduler::addThread(SchedulerThread* thread)
        {
            if( not Self::isConstructed() ) return false;
            bool_t const is = Interrupt::disableAll();
            bool_t res = threads_.add(thread);
            Interrupt::enableAll(is);
            return res;
        }

        /**
         * Removes the first occurrence of the specified thread.
         *
         * @param thread removing thread.
         */
        void Scheduler::removeThread(SchedulerThread* thread)
        {
            if( not Self::isConstructed() ) return;
            bool_t const is = Interrupt::disableAll();
            threads_.removeElement(thread);
            Interrupt::enableAll(is);
        }
    }
}
