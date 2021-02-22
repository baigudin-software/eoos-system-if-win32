/**
 * @brief Global thread switching controller.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_GLOBAL_THREAD_HPP_
#define SYS_GLOBAL_THREAD_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Toggle.hpp"

namespace eoos
{
namespace sys
{

/**
 * @brief Global thread switching class.
 */
class GlobalThread : public NonCopyable, public api::Toggle
{
    using Self = GlobalThread;
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    GlobalThread() : Parent()
    {
    }

    /**
     * @brief Destructor.
     */
    ~GlobalThread() override
    {
    }

    /**
     * @brief Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t isConstructed() const override
    {
        return Parent::isConstructed();
    }

    /**
     * @brief Disables thread switching.
     *
     * @return Global thread enable bit value before method was called.
     */
    bool_t disable() override
    {
        return false;
    }

    /**
     * @brief Enables thread switching.
     *
     * @param status Returned status by disable method.
     */
    void enable(bool_t) override
    {
    }

};

} // namespace sys
} // namespace eoos
#endif // SYS_GLOBAL_THREAD_HPP_
