/**
 * @file      sys.Heap.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_HEAP_HPP_
#define SYS_HEAP_HPP_

#include "api.Heap.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Heap.
 * @brief Heap class.
 */
class Heap : public api::Heap
{

public:

    /**
     * @brief Constructor.
     */
    Heap() noexcept;
    
    /**
     * @brief Destructor.
     */
    ~Heap() noexcept override = default;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override;
    
    /**
     * @copydoc eoos::api::Heap::allocate(size_t,void*)
     */
    void* allocate(size_t const size, void* ptr) noexcept override;

    /**
     * @copydoc eoos::api::Heap::free(void*)
     */
    void free(void* ptr) noexcept override;
    
private:
    
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
