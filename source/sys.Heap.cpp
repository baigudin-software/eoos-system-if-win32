/**
 * @file      sys.Heap.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.Heap.hpp"

namespace eoos
{
namespace sys
{

Heap::Heap() noexcept 
    : api::Heap() {
}

bool_t Heap::isConstructed() const noexcept
{
    return true;
}

void* Heap::allocate(size_t const size, void* ptr) noexcept try
{    
    static_cast<void>(ptr); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
    #ifndef EOOS_GLOBAL_ENABLE_NO_HEAP
    return new ucell_t[size];
    #else
    static_cast<void>(size); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
    return NULLPTR;
    #endif // EOOS_GLOBAL_ENABLE_NO_HEAP
} catch (...) { ///< UT Justified Branch: OS dependency
    return NULLPTR;
}

void Heap::free(void* ptr) noexcept
{
    #ifndef EOOS_GLOBAL_ENABLE_NO_HEAP
    ucell_t* addr{ static_cast<ucell_t*>(ptr) }; ///< SCA AUTOSAR-C++14 Justified Rule M5-2-8
    delete[] addr;
    #else
    static_cast<void>(ptr); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
    #endif // EOOS_GLOBAL_ENABLE_NO_HEAP
}
    
} // namespace sys
} // namespace eoos
