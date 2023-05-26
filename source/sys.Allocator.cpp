/**
 * @file      sys.Allocator.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.Allocator.hpp"
#include "sys.Call.hpp"

namespace eoos
{
namespace sys
{
 
void* Allocator::allocate(size_t size)
{
    return sys::Call::get().getHeap().allocate(size, NULLPTR);
}

void Allocator::free(void* ptr)
{
    return sys::Call::get().getHeap().free(ptr);    
}

} // namespace sys
} // namespace eoos
