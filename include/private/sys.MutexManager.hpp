/**
 * @file      sys.MutexManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_MUTEXMANAGER_HPP_
#define SYS_MUTEXMANAGER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.MutexManager.hpp"
#include "sys.Mutex.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class MutexManager.
 * @brief Mutex sub-system manager.
 */
class MutexManager : public NonCopyable, public api::MutexManager
{
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    MutexManager() noexcept 
        : NonCopyable()
        , api::MutexManager() {
        setConstructed( true );
    }

    /**
     * @brief Destructor.
     */
    ~MutexManager() noexcept override
    {
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override
    {
        return Parent::isConstructed();
    }    

    /**
     * @copydoc eoos::api::MutexManager::create()
     */
    api::Mutex* create() noexcept override try
    {
        lib::UniquePointer<api::Mutex> res;
        if( isConstructed() )
        {   
            res.reset( new Mutex() ); ///< SCA AUTOSAR-C++14 Justified Rule A18-5-2
            if( !res.isNull() )
            {
                if( !res->isConstructed() )
                {   ///< UT Justified Branch: HW dependency
                    res.reset();
                }
            }
        }
        return res.release();
    } catch (...) { ///< UT Justified Branch: OS dependency
        return NULLPTR;
    }

    /**
     * @copydoc eoos::api::MutexManager::remove()
     */
    void remove(api::Mutex* mutex) noexcept override
    {
        if( isConstructed() && mutex != NULLPTR )
        {
            delete mutex;
        }
    }

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
