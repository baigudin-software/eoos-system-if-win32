/**
 * @file      sys.SystemMutex.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SYSTEMMUTEX_HPP_
#define SYS_SYSTEMMUTEX_HPP_

#include "sys.NonCopyable.hpp"
#include "api.SystemMutex.hpp"
#include "sys.Mutex.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class SystemMutex.
 * @brief Mutex sub-system.
 */
class SystemMutex : public NonCopyable, public api::SystemMutex
{
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    SystemMutex() noexcept 
        : NonCopyable()
        , api::SystemMutex() {
        setConstructed( true );
    }

    /**
     * @brief Destructor.
     */
    ~SystemMutex() noexcept override
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
     * @copydoc eoos::api::SystemMutex::create()
     */
    api::Mutex* create() override try
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
     * @copydoc eoos::api::SystemMutex::remove()
     */
    void remove(api::Mutex* mutex) override
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
    SystemMutex(SystemMutex const&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    SystemMutex& operator=(SystemMutex const&) noexcept = delete;   

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    SystemMutex(SystemMutex&&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    SystemMutex& operator=(SystemMutex&&) & noexcept = delete;        

};

} // namespace sys
} // namespace eoos
#endif // SYS_SYSTEMMUTEX_HPP_
