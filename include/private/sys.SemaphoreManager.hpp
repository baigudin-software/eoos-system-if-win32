/**
 * @file      sys.SemaphoreManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHOREMANAGER_HPP_
#define SYS_SEMAPHOREMANAGER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.SemaphoreManager.hpp"
#include "sys.Semaphore.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class SemaphoreManager.
 * @brief Semaphore sub-system manager.
 */
class SemaphoreManager : public NonCopyable, public api::SemaphoreManager
{
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    SemaphoreManager() noexcept 
        : NonCopyable()
        , api::SemaphoreManager() {
        setConstructed( true );
    }

    /**
     * @brief Destructor.
     */
    ~SemaphoreManager() noexcept override
    {
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const override
    {
        return Parent::isConstructed();
    }    

    /**
     * @copydoc eoos::api::SemaphoreManager::create()
     */
    api::Semaphore* create(int32_t permits) override try
    {
        lib::UniquePointer<api::Semaphore> res;
        if( isConstructed() )
        {
            res.reset( new Semaphore(permits) ); ///< SCA AUTOSAR-C++14 Justified Rule A18-5-2
            if( !res.isNull() )
            {   ///< UT Justified Branch: HW dependency
                if( !res->isConstructed() )
                {
                    res.reset();
                }
            }
        }
        return res.release();
    } catch (...) { ///< UT Justified Branch: OS dependency
        return NULLPTR;
    }

    /**
     * @copydoc eoos::api::SemaphoreManager::remove()
     */
    void remove(api::Semaphore* semaphore) override
    {
        if( isConstructed() && semaphore != NULLPTR )
        {
            delete semaphore;
        }
    }

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
