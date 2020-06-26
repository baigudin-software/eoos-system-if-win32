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
        Scheduler::Scheduler() : Parent(),
            globalThread_  (),
            threads_       (NULLPTR){
            setConstructed( construct() );
        }

        Scheduler::~Scheduler()
        {
        }

        bool_t Scheduler::isConstructed() const
        {
            return Parent::isConstructed();
        }

        api::Thread* Scheduler::createThread(api::Task& task)
        {
            if( not Self::isConstructed() ) return NULLPTR;
            SchedulerThread* thread = new SchedulerThread(task, this);
            if(thread == NULLPTR) return NULLPTR;
            if(thread->isConstructed()) return thread;
            delete thread;
            return NULLPTR;
        }

        api::Thread& Scheduler::getCurrentThread() const
        {
            if( not Self::isConstructed() )
            {
                System::exit(ERROR_SYSCALL_CALLED);
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
                System::exit(ERROR_RESOURCE_NOT_FOUND);
            }
            Interrupt::enableAll(is);
            return *thread;
        }

        void Scheduler::yield()
        {
            if( not Self::isConstructed() )
            {
                System::exit(ERROR_SYSCALL_CALLED);
            }
            // TODO: sched_yield();
        }

        api::Toggle& Scheduler::toggle()
        {
            return globalThread_;
        }

        bool_t Scheduler::construct()
        {
            if( not isConstructed() ) return false;
            if( not globalThread_.isConstructed() ) return false;
            if( not threads_.isConstructed() ) return false;
            return true;
        }

        bool_t Scheduler::addThread(SchedulerThread* thread)
        {
            if( not Self::isConstructed() ) return false;
            bool_t const is = Interrupt::disableAll();
            bool_t res = threads_.add(thread);
            Interrupt::enableAll(is);
            return res;
        }

        void Scheduler::removeThread(SchedulerThread* thread)
        {
            if( not Self::isConstructed() ) return;
            bool_t const is = Interrupt::disableAll();
            threads_.removeElement(thread);
            Interrupt::enableAll(is);
        }
    }
}
