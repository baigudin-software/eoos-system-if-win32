/**
 * @file      sys.SemaphoreManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHOREMANAGER_HPP_
#define SYS_SEMAPHOREMANAGER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.SemaphoreManager.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class SemaphoreManager.
 * @brief Semaphore sub-system manager.
 */
class SemaphoreManager : public NonCopyable<NoAllocator>, public api::SemaphoreManager
{
    using Parent = NonCopyable<NoAllocator>;

public:

    /**
     * @brief Constructor.
     */
    SemaphoreManager() noexcept;

    /**
     * @brief Destructor.
     */
    ~SemaphoreManager() noexcept override = default;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override;

    /**
     * @copydoc eoos::api::SemaphoreManager::create()
     */
    api::Semaphore* create(int32_t permits) noexcept override;

    /**
     * @copydoc eoos::api::SemaphoreManager::remove()
     */
    void remove(api::Semaphore* semaphore) noexcept override;

private:
    
    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    SemaphoreManager(SemaphoreManager const&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    SemaphoreManager& operator=(SemaphoreManager const&) noexcept = delete;   

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    SemaphoreManager(SemaphoreManager&&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    SemaphoreManager& operator=(SemaphoreManager&&) & noexcept = delete;        

};

} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHOREMANAGER_HPP_
