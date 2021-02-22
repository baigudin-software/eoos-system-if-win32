/**
 * @brief Runtime system execution.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_RUNTIME_HPP_
#define SYS_RUNTIME_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Runtime.hpp"

namespace eoos
{
namespace sys
{

/**
 * @brief Runtime system execution class.
 */
class Runtime : public NonCopyable, public api::Runtime
{
    using Self = Runtime;
    using Parent = NonCopyable;

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
    ~Runtime() override
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
     * @brief Loads a program for executing.
     *
     * @param path A system path to a program.
     * @return true if program has been loaded successfully.
     */
    bool_t load(const char_t* const path) override
    {
        if( not Self::isConstructed() ) return false;
        return false;
    }

    /**
     * @brief Terminates a system execution.
     *
     * @param status A termination status.
     */
    void exit(int32_t const status) override
    {
        // @todo 
        volatile bool_t const isTerminate = true;
        while( isTerminate ){};
    }

};

} // namespace sys
} // namespace eoos
#endif // SYS_RUNTIME_HPP_
