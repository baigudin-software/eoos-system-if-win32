/**
 * @brief The operating system heap memory.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018-2021, Sergey Baigudin, Baigudin Software
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
 * @brief The operating system heap memory class.
 */
class Heap : public NonCopyable, public api::Heap
{
    using Self = Heap;
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    Heap();

    /**
     * @brief Destructor.
     */
    ~Heap() override;

    /**
     * @brief Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t isConstructed() const override;

    /**
     * @brief Allocates memory.
     *
     * @param size Required memory size in byte.
     * @param ptr  NULLPTR value becomes to allocate memory, and
     *             other given values are simply returned
     *             as memory address.
     * @return pointer to allocated memory or NULLPTR.
     */
    void* allocate(size_t size, void* ptr) override;

    /**
     * @brief Frees an allocated memory.
     *
     * @param ptr Pointer to allocated memory.
     */
    void free(void* ptr) override;

};

} // namespace sys
} // namespace eoos
#endif // SYS_HEAP_HPP_
