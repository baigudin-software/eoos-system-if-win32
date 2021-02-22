/**
 * @brief Thread tasks scheduler.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SCHEDULER_HPP_
#define SYS_SCHEDULER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Scheduler.hpp"
#include "sys.GlobalThread.hpp"

namespace eoos
{
namespace sys
{

/**
 * @brief Thread tasks scheduler class.
 */
class Scheduler : public NonCopyable, public api::Scheduler
{
    using Self = Scheduler;
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    Scheduler();

    /**
     * @brief Destructor.
     */
    ~Scheduler() override;

    /**
     * @brief Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t isConstructed() const override;

    /**
     * @brief Creates a new thread.
     *
     * @param task An user task which main method will be invoked when created thread is started.
     * @return A new thread.
     */
    api::Thread* createThread(api::Task& task) override;

    /**
     * @brief Returns currently executing thread.
     *
     * @return Executing thread.
     */
    api::Thread& getCurrentThread() const override;
    
    /**
     * @brief Causes current thread to sleep.
     *
     * @param millis - a time to sleep in milliseconds.
     * @param nanos  - an additional nanoseconds to sleep.
     */
    void sleepCurrentThread(int64_t millis, int32_t nanos = 0) override;        

    /**
     * @brief Yields to next thread.
     */
    void yield() override;

    /**
     * @brief Returns the toggle interface for controlling global thread switching.
     *
     * @return Toggle interface to disable and enable thread switching.
     */
    api::Toggle& toggle() override;

private:

    /**
     * @brief Constructor.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct();

    /**
     * @brief Global thread switching controller.
     */
    GlobalThread globalThread_ {};

};

} // namespace sys
} // namespace eoos
#endif // SYS_SCHEDULER_HPP_
