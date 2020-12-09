/**
 * @brief Hardware global interrupts resource.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_GLOBAL_INTERRUPT_HPP_
#define SYS_GLOBAL_INTERRUPT_HPP_

#include "sys.Object.hpp"
#include "api.Toggle.hpp"

namespace eoos
{
namespace sys
{

class GlobalInterrupt : public Object, public api::Toggle
{
    typedef GlobalInterrupt Self;
    typedef ::eoos::sys::Object Parent;

public:

    /**
     * @brief Constructor.
     */
    GlobalInterrupt() : Parent()
    {
    }

    /**
     * @brief Destructor.
     */
    virtual ~GlobalInterrupt()
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
    GlobalInterrupt(const GlobalInterrupt& obj);

    /**
     * @brief Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.
     */
    GlobalInterrupt& operator =(const GlobalInterrupt& obj);

};

} // namespace sys
} // namespace eoos
#endif // SYS_GLOBAL_INTERRUPT_HPP_
