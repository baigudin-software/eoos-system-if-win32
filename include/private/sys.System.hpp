/**
 * The operating system class.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SYSTEM_HPP_
#define SYS_SYSTEM_HPP_

#include "sys.Object.hpp"
#include "api.System.hpp"
#include "sys.Heap.hpp"
#include "sys.GlobalInterrupt.hpp"
#include "sys.Runtime.hpp"
#include "sys.Scheduler.hpp"
#include "Error.hpp"

namespace eoos
{
    namespace sys
    {
        class System : public Object, public api::System
        {
            typedef System Self;
            typedef ::eoos::sys::Object Parent;

        public:

            /**
             * Constructor.
             */
            System();

            /**
             * Destructor.
             */
            virtual ~System();

            /**
             * Tests if this object has been constructed.
             *
             * @return true if object has been constructed successfully.
             */
            virtual bool_t isConstructed() const;

            /**
             * Returns running time of the operating system in nanoseconds.
             *
             * @return time in nanoseconds.
             */
            virtual int64_t getTime() const;

            /**
             * Returns the operating system heap memory.
             *
             * @return the heap memory.
             */
            virtual api::Heap& getHeap() const;

            /**
             * Returns the system runtime environment.
             *
             * @return the system runtime environment.
             */
            virtual api::Runtime& getRuntime() const;

            /**
             * Returns a global interrupt controller.
             *
             * @return a global interrupt controller.
             */
            virtual api::Toggle& getGlobalInterrupt() const;

            /**
             * Returns the kernel scheduler.
             *
             * @return the kernel scheduler.
             */
            virtual api::Scheduler& getScheduler() const;

            /**
             * Creates a new mutex resource.
             *
             * @return a new mutex resource, or NULLPTR if an error has been occurred.
             */
            virtual api::Mutex* createMutex();

            /**
             * Creates a new semaphore resource.
             *
             * @param permits - the initial number of permits available.
             * @param isFair  - true if this semaphore will guarantee FIFO granting of permits under contention.
             * @return a new semaphore resource, or NULLPTR if an error has been occurred.
             */
            virtual api::Semaphore* createSemaphore(int32_t permits, bool_t isFair);

            /**
             * Creates a new interrupt resource.
             *
             * @param handler - user class which implements an interrupt handler interface.
             * @param source  - available interrupt source number.
             * @return a new interrupt resource, or NULLPTR if an error has been occurred.
             */
            virtual api::Interrupt* createInterrupt(api::Task& handler, int32_t source);

            /**
             * Terminates the system execution.
             */
            virtual void terminate() const;

            /**
             * Executes the operating system.
             *
             * @return zero, or error code if the execution has been terminated.
             */
            int32_t execute();

            /**
             * Returns the operating system syscall interface.
             *
             * @return the operating system syscall interface.
             */
            static api::System& call();

            /**
             * Terminates the system execution.
             *
             * @param error an exit code.
             */
            static void exit(Error error);

        private:

            /**
             * Constructs this object.
             *
             * @return true if object has been constructed successfully.
             */
            bool_t construct();

            /**
             * Proves a resource.
             *
             * @param a resource.
             * @return a passed resource, or NULLPTR if the resource has not been approved.
             */
            template <class T>
            static T* proveResource(T* res)
            {
                if(res != NULLPTR)
                {
                    if( not res->isConstructed() )
                    {
                        delete res;
                        res = NULLPTR;
                    }
                }
                return res;
            }

            /**
             * Copy constructor.
             *
             * @param obj a reference to source object.
             */
            System(const System& obj);

            /**
             * Assignment operator.
             *
             * @param obj a reference to source object.
             * @return reference to this object.
             */
            System& operator =(const System& obj);

            /**
             * The operating system interface.
             */
            static api::System* system_;

            /**
             * The operating system heap memory.
             */
            mutable Heap heap_;

            /**
             * The operating system global interrupt controller.
             */
            mutable GlobalInterrupt gi_;

            /**
             * The operating system runtime environment.
             */
            mutable Runtime runtime_;

            /**
             * The operating system scheduler.
             */
            mutable Scheduler scheduler_;

        };
    }
}
#endif // SYS_SYSTEM_HPP_
