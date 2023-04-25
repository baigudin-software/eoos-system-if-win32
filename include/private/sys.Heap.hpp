/**
 * @file      sys.Heap.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_HEAP_HPP_
#define SYS_HEAP_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Heap.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Heap.
 * @brief Heap class.
 */
class Heap : public NonCopyable, public api::Heap
{
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    Heap() noexcept 
        : NonCopyable()
        , api::Heap() {
        bool_t const isConstructed{ construct() };
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    ~Heap() noexcept override = default;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override ///< SCA AUTOSAR-C++14 Defected Rule A10-2-1
    {
        return Parent::isConstructed();
    }
    
    /**
     * @copydoc eoos::api::Heap::allocate(size_t,void*)
     */
    void* allocate(size_t const size, void* ptr) noexcept override try ///< SCA AUTOSAR-C++14 Justified Rule A8-4-8
    {    
        static_cast<void>(ptr); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
        #ifndef EOOS_GLOBAL_ENABLE_NO_HEAP
        return new ucell_t[size];
        #else
        static_cast<void>(size); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
        return NULLPTR;
        #endif // EOOS_GLOBAL_ENABLE_NO_HEAP
    } catch (...) {
        return NULLPTR;
    }

    /**
     * @copydoc eoos::api::Heap::free(void*)
     */
    void free(void* ptr) noexcept override ///< SCA AUTOSAR-C++14 Justified Rule A8-4-8
    {
        #ifndef EOOS_GLOBAL_ENABLE_NO_HEAP
        ucell_t* addr{ static_cast<ucell_t*>(ptr) }; ///< SCA AUTOSAR-C++14 Justified Rule M5-2-8
        delete[] addr;
        #else
        static_cast<void>(ptr); // Avoid MISRA-C++:2008 Rule 0–1–3 and AUTOSAR C++14 Rule A0-1-4
        #endif // EOOS_GLOBAL_ENABLE_NO_HEAP
    }
    
private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct() const noexcept
    {
        bool_t res{ false };
        if( isConstructed() )
        {
            res = true;
        }
        return res;
    }
    
    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    Heap(Heap const&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    Heap& operator=(Heap const&) noexcept = delete;   

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    Heap(Heap&&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    Heap& operator=(Heap&&) & noexcept = delete;        

};

} // namespace sys
} // namespace eoos
#endif // SYS_HEAP_HPP_
