/**
 * @brief Root class of the operating system for objects which cannot be copied.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_NON_COPYABLE_HPP_
#define SYS_NON_COPYABLE_HPP_

#include "sys.Object.hpp"

namespace eoos
{
namespace sys
{

/**
 * @brief Root class of the operating system for objects which cannot be copied.
 */
class NonCopyable : public Object
{
    using Parent = Object;

public:

    /**
     * @brief Constructor.
     */
    NonCopyable() noexcept : Parent() {}

    /**
     * @brief Destructor.
     */
    ~NonCopyable() noexcept override {}
    
private:
    
    /**
     * @brief Copy constructor.
     *
     * @param obj Reference to a source object.
     */
    NonCopyable(const NonCopyable& obj) noexcept = delete;
    
    /**
     * @brief Copy assignment operator.
     *
     * @param obj Reference to a source object.
     * @return Reference to this object.
     */       
    NonCopyable& operator=(const NonCopyable& obj) noexcept = delete;   

    /**
     * @brief Move constructor.
     *
     * @param obj Right reference to a source object.     
     */       
    NonCopyable(NonCopyable&& obj) noexcept = delete;
    
    /**
     * @brief Move assignment operator.
     *
     * @param obj Right reference to a source object.
     * @return Reference to this object.
     */
    NonCopyable& operator=(NonCopyable&& obj) noexcept = delete;

};

} // namespace sys
} // namespace eoos
#endif // SYS_NON_COPYABLE_HPP_
