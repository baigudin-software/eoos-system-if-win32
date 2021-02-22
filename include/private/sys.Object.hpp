/**
 * @brief Root class of the operating system class hierarchy.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OBJECT_HPP_
#define SYS_OBJECT_HPP_

#include "Object.hpp"
#include "lib.Types.hpp"

namespace eoos
{
namespace sys
{

/**
 * @brief Root class of the operating system.
 */
class Object : public ::eoos::Object<Allocator>
{
    using Parent = ::eoos::Object<Allocator>;

public:

    /**
     * @brief Constructor.
     */
    Object() noexcept : Parent() {}

    /**
     * @brief Destructor.
     */
    ~Object() noexcept override {}
    
    /**
     * @brief Copy constructor.
     *
     * @param obj - reference to a source object.
     */
    Object(const Object& obj) noexcept : Parent(obj) {} 
    
    /**
     * @brief Copy assignment operator.
     *
     * @param obj - reference to a source object.
     * @return reference to this object.
     */       
    Object& operator=(const Object& obj) noexcept
    {
        Parent::operator=(obj);
        return *this;
    }    

    /**
     * @brief Move constructor.
     *
     * @param obj - right reference to a source object.     
     */       
    Object(Object&& obj) noexcept : Parent( lib::move(obj) ) {}
    
    /**
     * @brief Move assignment operator.
     *
     * @param obj - right reference to a source object.
     * @return reference to this object.
     */
    Object& operator=(Object&& obj) noexcept
    {
        Parent::operator=( lib::move(obj) );
        return *this;
    }

};

} // namespace sys
} // namespace eoos
#endif // SYS_OBJECT_HPP_
