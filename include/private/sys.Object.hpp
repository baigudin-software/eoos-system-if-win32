/**
 * @file      sys.Object.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OBJECT_HPP_
#define SYS_OBJECT_HPP_

#include "Object.hpp"
#include "sys.Types.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Object
 * @brief Root class of the operating system class hierarchy.
 */
class Object : public ::eoos::Object<>
{
    using Parent = ::eoos::Object<>;

public:

    /**
     * @brief Constructor.
     */
    Object() = default;

    /**
     * @brief Destructor.
     */
    ~Object() override = default;
    
protected:

    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    Object(Object const& obj) noexcept 
        : ::eoos::Object<>(obj) {
    } 
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    Object& operator=(Object const& obj) & noexcept ///< SCA AUTOSAR-C++14 Justified Rule A10-2-1
    {
        Parent::operator=(obj);
        return *this;
    }    

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    Object(Object&& obj) noexcept ///< SCA AUTOSAR-C++14 Defected Rule A8-4-8
        : ::eoos::Object<>( lib::move(obj) ) {
    }
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    Object& operator=(Object&& obj) & noexcept ///< SCA AUTOSAR-C++14 Justified Rule A10-2-1 and Defected Rule A8-4-8
    {
        Parent::operator=( lib::move(obj) );
        return *this;
    }

};

} // namespace sys
} // namespace eoos
#endif // SYS_OBJECT_HPP_
