/**
 * @brief The operating system.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SYSTEM_HPP_
#define SYS_SYSTEM_HPP_

#include "sys.NonCopyable.hpp"
#include "api.System.hpp"
#include "sys.Heap.hpp"
#include "sys.Runtime.hpp"
#include "sys.Scheduler.hpp"
#include "sys.Error.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @brief The operating system class.
 */
class System : public NonCopyable, public api::System
{
    using Self = System;
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    System();

    /**
     * @brief Destructor.
     */
    ~System() override;

    /**
     * @brief Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t isConstructed() const override;

    /**
     * @brief Returns running time of the operating system in nanoseconds.
     *
     * @return time in nanoseconds.
     */
    int64_t getTime() const override;

    /**
     * @brief Returns the operating system heap memory.
     *
     * @return the heap memory.
     */
    api::Heap& getHeap() const override;

    /**
     * @brief Returns the system runtime environment.
     *
     * @return the system runtime environment.
     */
    api::Runtime& getRuntime() const override;

    /**
     * @brief Returns the kernel scheduler.
     *
     * @return the kernel scheduler.
     */
    api::Scheduler& getScheduler() const override;

    /**
     * @brief Creates a new mutex resource.
     *
     * @return a new mutex resource, or NULLPTR if an error has been occurred.
     */
    api::Mutex* createMutex() override;

    /**
     * @brief Creates a new semaphore resource.
     *
     * @param permits - the initial number of permits available.
     * @param isFair  - true if this semaphore will guarantee FIFO granting of permits under contention.
     * @return a new semaphore resource, or NULLPTR if an error has been occurred.
     */
    api::Semaphore* createSemaphore(int32_t permits, bool_t isFair) override;

    /**
     * @brief Terminates the system execution.
     */
    void terminate() const override;

    /**
     * @brief Executes the operating system.
     *
     * @return zero, or error code if the execution has been terminated.
     */
    int32_t execute();

    /**
     * @brief Returns the operating system syscall interface.
     *
     * @return the operating system syscall interface.
     */
    static api::System& call();

    /**
     * @brief Terminates the system execution.
     *
     * @param error an exit code.
     */
    static void exit(Error error);

private:

    /**
     * @brief Constructs this object.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Proves a resource.
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
     * @brief The operating system interface.
     */
    static api::System* system_;

    /**
     * @brief The operating system heap memory.
     */
    mutable Heap heap_ {};

    /**
     * @brief The operating system runtime environment.
     */
    mutable Runtime runtime_ {};

    /**
     * @brief The operating system scheduler.
     */
    mutable Scheduler scheduler_ {};

};

} // namespace sys
} // namespace eoos
#endif // SYS_SYSTEM_HPP_
