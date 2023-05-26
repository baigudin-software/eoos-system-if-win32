/**
 * @file      sys.Allocator.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_ALLOCATOR_HPP_
#define SYS_ALLOCATOR_HPP_

#include "sys.Types.hpp"

namespace eoos
{
namespace sys
{
 
/**
 * @class Allocator
 * @brief Memory allocator.
 */ 
class Allocator final
{

public:

    /**
     * @brief Allocates memory.
     *
     * @param size Number of bytes to allocate.
     * @return Allocated memory address or a null pointer.
     */
    static void* allocate(size_t size);
    
    /**
     * @brief Frees allocated memory.
     *
     * @param ptr Address of allocated memory block or a null pointer.
     */
    static void free(void* ptr);
    
};

} // namespace sys
} // namespace eoos

#endif // SYS_ALLOCATOR_HPP_
