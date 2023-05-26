/**
 * @file      sys.Object.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OBJECT_HPP_
#define SYS_OBJECT_HPP_

#include "lib.Object.hpp"
#include "sys.Allocator.hpp"
#include "sys.NoAllocator.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Object
 * @brief Root class of the operating system class hierarchy.
 *
 * @tparam A Heap memory allocator class.
 */
template <class A>
class Object : public lib::Object<A>
{
    using Parent = lib::Object<A>;

public:

    /**
     * @brief Constructor.
     */
    Object() noexcept = default;

    /**
     * @brief Destructor.
     */
    ~Object() noexcept override = default;
    
protected:

    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    Object(Object const& obj) noexcept;
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    Object& operator=(Object const& obj) & noexcept;

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    Object(Object&& obj) noexcept;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    Object& operator=(Object&& obj) & noexcept;

};

template <class A>
Object<A>::Object(Object const& obj) noexcept 
    : lib::Object<A>(obj) {
} 

template <class A>
Object<A>& Object<A>::operator=(Object const& obj) & noexcept
{
    Parent::operator=(obj);
    return *this;
}    

template <class A>
Object<A>::Object(Object&& obj) noexcept
    : lib::Object<A>( lib::move(obj) ) {
}

template <class A>
Object<A>& Object<A>::operator=(Object&& obj) & noexcept
{
    Parent::operator=( lib::move(obj) );
    return *this;
}

} // namespace sys
} // namespace eoos
#endif // SYS_OBJECT_HPP_
