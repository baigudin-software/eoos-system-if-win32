/**
 * @brief Root class of the operating system class hierarchy.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2020, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OBJECT_HPP_
#define SYS_OBJECT_HPP_

#include "Object.hpp"

namespace eoos
{
namespace sys
{

class Object : public ::eoos::Object<Allocator>
{
    typedef ::eoos::Object<Allocator> Parent;

public:

    /**
     * @brief Constructor.
     */
    Object();

    /**
     * @brief Destructor.
     */
    virtual ~Object();

};

} // namespace sys
} // namespace eoos
#endif // SYS_OBJECT_HPP_
