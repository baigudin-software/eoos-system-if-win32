/**
 * The operating system class.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2020, Sergey Baigudin, Baigudin Software
 */
#include "sys.System.hpp"
#include "sys.Mutex.hpp"
#include "sys.Semaphore.hpp"
#include "sys.Interrupt.hpp"
#include "Program.hpp"

namespace eoos
{
    namespace sys
    {
        /**
         * Calls the operating system.
         *
         * @return the operating system syscall interface.
         */
        api::System& syscall()
        {
            return System::call();
        }

        /**
         * Constructor.
         */
        System::System() : Parent(),
            heap_      (),
            gi_        (),
            runtime_   (),
            scheduler_ (){
            bool_t const isConstructed = construct();
            setConstructed( isConstructed );
        }

        /**
         * Destructor.
         */
        System::~System()
        {
        }

        /**
         * Tests if this object has been constructed.
         *
         * @return true if object has been constructed successfully.
         */
        bool_t System::isConstructed() const
        {
            return Parent::isConstructed();
        }

        /**
         * Returns running time of the operating system in nanoseconds.
         *
         * @return time in nanoseconds.
         */
        int64_t System::getTime() const
        {
            return 0;
        }

        /**
         * Returns the operating system heap memory.
         *
         * @return the heap memory.
         */
        api::Heap& System::getHeap() const
        {
            if( not Self::isConstructed() )
            {
                terminate(ERROR_SYSCALL_CALLED);
            }
            return heap_;
        }

        /**
         * Returns the system runtime environment.
         *
         * @return the system runtime environment.
         */
        api::Runtime& System::getRuntime() const
        {
            if( not Self::isConstructed() )
            {
                terminate(ERROR_SYSCALL_CALLED);
            }
            return runtime_;
        }

        /**
         * Returns a global interrupt controller.
         *
         * @return a global interrupt controller.
         */
        api::Toggle& System::getGlobalInterrupt() const
        {
            if( not Self::isConstructed() )
            {
                terminate(ERROR_SYSCALL_CALLED);
            }
            return gi_;
        }

        /**
         * Returns the kernel scheduler.
         *
         * @return the kernel scheduler.
         */
        api::Scheduler& System::getScheduler() const
        {
            if( not Self::isConstructed() )
            {
                terminate(ERROR_SYSCALL_CALLED);
            }
            return scheduler_;
        }

        /**
         * Creates a new mutex resource.
         *
         * @return a new mutex resource, or NULLPTR if an error has been occurred.
         */
        api::Mutex* System::createMutex()
        {
            api::Mutex* res = new Mutex();
            return proveResource(res);
        }

        /**
         * Creates a new semaphore resource.
         *
         * @param permits - the initial number of permits available.
         * @param isFair  - true if this semaphore will guarantee FIFO granting of permits under contention.
         * @return a new semaphore resource, or NULLPTR if an error has been occurred.
         */
        api::Semaphore* System::createSemaphore(int32_t permits, bool_t isFair)
        {
            api::Semaphore* res = new Semaphore(permits);
            return proveResource(res);
        }

        /**
         * Creates a new interrupt resource.
         *
         * @param handler - user class which implements an interrupt handler interface.
         * @param source  - available interrupt source number.
         * @return a new interrupt resource, or NULLPTR if an error has been occurred.
         */
        api::Interrupt* System::createInterrupt(api::Task& handler, int32_t source)
        {
            api::Interrupt* res = new Interrupt(handler, source);
            return proveResource(res);
        }

        /**
         * Terminates the operating system execution.
         *
         * @param status a termination status.
         */
        void System::terminate() const
        {
            terminate(ERROR_USER_TERMINATION);
        }

        /**
         * Executes the operating system.
         *
         * @return zero, or error code if the execution has been terminated.
         */
        int32_t System::execute()
        {
            int32_t error;
            if( not Self::isConstructed() )
            {
                error = ERROR_UNDEFINED;
            }
            else
            {
                error = Program::start();
            }
            return error;
        }

        /**
         * Returns the operating system syscall interface.
         *
         * @return the operating system syscall interface.
         */
        api::System& System::call()
        {
            if(system_ == NULLPTR)
            {
                terminate(ERROR_SYSCALL_CALLED);
            }
            return *system_;
        }

        /**
         * Terminates the operating system execution.
         *
         * @param error a termination status code.
         */
        void System::terminate(Error)
        {
            // ... TODO ...
            bool_t const is = Interrupt::disableAll();
            volatile bool_t const isTerminate = true;
            while( isTerminate ){};
            Interrupt::enableAll(is);
        }

        /**
         * Constructs this object.
         *
         * @return true if object has been constructed successfully.
         */
        bool_t System::construct()
        {
            bool_t res = Self::isConstructed();
            while(res == true)
            {
                if( system_ != NULLPTR )
                {
                    res = false;
                    continue;
                }
                if( not heap_.isConstructed() )
                {
                    res = false;
                    continue;
                }
                if( not gi_.isConstructed() )
                {
                    res = false;
                    continue;
                }
                if( not runtime_.isConstructed() )
                {
                    res = false;
                    continue;
                }
                if( not scheduler_.isConstructed() )
                {
                    res = false;
                    continue;
                }
                // The construction completed successfully
                system_ = this;
                break;
            }
            return res;
        }

        /**
         * The operating system interface.
         */
        api::System* System::system_ = NULLPTR;
    }
}
