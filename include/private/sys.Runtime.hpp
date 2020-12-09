/**
 * @brief Runtime system execution.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_RUNTIME_HPP_
#define SYS_RUNTIME_HPP_

#include "sys.Object.hpp"
#include "api.Runtime.hpp"
#include "sys.Interrupt.hpp"

namespace eoos
{
namespace sys
{

class Runtime : public Object, public api::Runtime
{
    typedef Runtime Self;
    typedef ::eoos::sys::Object Parent;

public:

    /**
     * @brief Constructor.
     */
    Runtime() : Parent()
    {
    }

    /**
     * @brief Destructor.
     */
    virtual ~Runtime()
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
     * @brief Loads a program for executing.
     *
     * @param path a system path to a program.
     * @return true if program has been loaded successfully.
     */
    virtual bool_t load(const char_t* path)
    {
        if( not Self::isConstructed() ) return false;
        return false;
    }

    /**
     * @brief Terminates a system execution.
     *
     * @param status a termination status.
     */
    virtual void exit(int32_t const status)
    {
        // ... TODO ...
        bool_t const is = Interrupt::disableAll();
        volatile bool_t const isTerminate = true;
        while( isTerminate ){};
        Interrupt::enableAll(is);
    }

private:

    /**
     * @brief Copy constructor.
     *
     * @param obj reference to source object.
     */
    Runtime(const Runtime& obj);

    /**
     * @brief Assignment operator.
     *
     * @param obj reference to source object.
     * @return reference to this object.
     */
    Runtime& operator =(const Runtime& obj);

};

} // namespace sys
} // namespace eoos
#endif // SYS_RUNTIME_HPP_
