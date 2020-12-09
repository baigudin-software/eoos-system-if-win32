/**
 * @brief Global thread switching controller.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_GLOBAL_THREAD_HPP_
#define SYS_GLOBAL_THREAD_HPP_

#include "sys.Object.hpp"
#include "api.Toggle.hpp"

namespace eoos
{
namespace sys
{

class GlobalThread : public Object, public api::Toggle
{
    typedef GlobalThread Self;
    typedef ::eoos::sys::Object Parent;

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
    virtual ~GlobalThread()
    {
    }

    /**
     * @brief Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */
    virtual bool_t isConstructed() const
    {
        return Parent::isConstructed();
    }

    /**
     * @brief Disables all maskable interrupts.
     *
     * @return global interrupt enable bit value before method was called.
     */
    virtual bool_t disable()
    {
        return false;
    }

    /**
     * @brief Enables all maskable interrupts.
     *
     * @param status returned status by disable method.
     */
    virtual void enable(bool_t status)
    {
    }

private:

    /**
     * @brief Copy constructor.
     *
     * @param obj reference to source object.
     */
    GlobalThread(const GlobalThread& obj);

    /**
     * @brief Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.
     */
    GlobalThread& operator =(const GlobalThread& obj);

};

} // namespace sys
} // namespace eoos
#endif // SYS_GLOBAL_THREAD_HPP_
