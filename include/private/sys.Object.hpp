/**
 * @file      sys.Object.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OBJECT_HPP_
#define SYS_OBJECT_HPP_

#include "lib.Object.hpp"
#include "sys.Types.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Object
 * @brief Root class of the operating system class hierarchy.
 */
class Object : public lib::Object<>
{
    using Parent = lib::Object<>;

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
    Object(Object const& obj) noexcept 
        : lib::Object<>(obj) {
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
        : lib::Object<>( lib::move(obj) ) {
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
