/**
 * @file      sys.NonCopyable.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_NONCOPYABLE_HPP_
#define SYS_NONCOPYABLE_HPP_

#include "sys.Object.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class NonCopyable
 * @brief Root class of the operating system for objects which cannot be copied.
 *
 * @tparam A Heap memory allocator class.
 */
template <class A>
class NonCopyable : public Object<A>
{

public:

    /**
     * @brief Constructor.
     */
    NonCopyable() noexcept = default;

    /**
     * @brief Destructor.
     */
    ~NonCopyable() noexcept override = default;
    
private:
    
    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    NonCopyable(NonCopyable const&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    NonCopyable& operator=(NonCopyable const&) noexcept = delete;   

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    NonCopyable(NonCopyable&&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    NonCopyable& operator=(NonCopyable&&) & noexcept = delete;

};

} // namespace sys
} // namespace eoos
#endif // SYS_NONCOPYABLE_HPP_
