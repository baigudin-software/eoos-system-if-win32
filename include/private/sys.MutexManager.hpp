/**
 * @file      sys.MutexManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_MUTEXMANAGER_HPP_
#define SYS_MUTEXMANAGER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.MutexManager.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class MutexManager.
 * @brief Mutex sub-system manager.
 */
class MutexManager : public NonCopyable<NoAllocator>, public api::MutexManager
{
    using Parent = NonCopyable<NoAllocator>;

public:

    /**
     * @brief Constructor.
     */
    MutexManager() noexcept;

    /**
     * @brief Destructor.
     */
    ~MutexManager() noexcept override = default;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override;

    /**
     * @copydoc eoos::api::MutexManager::create()
     */
    api::Mutex* create() noexcept override;

private:
    
    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    MutexManager(MutexManager const&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    MutexManager& operator=(MutexManager const&) noexcept = delete;   

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    MutexManager(MutexManager&&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    MutexManager& operator=(MutexManager&&) & noexcept = delete;        

};

} // namespace sys
} // namespace eoos
#endif // SYS_MUTEXMANAGER_HPP_
