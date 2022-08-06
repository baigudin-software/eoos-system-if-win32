/**
 * @file      sys.Mutex.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_MUTEX_HPP_
#define SYS_MUTEX_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Mutex.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Mutex.
 * @brief Mutex class.
 */
class Mutex : public NonCopyable, public api::Mutex
{
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    Mutex() noexcept 
        : NonCopyable()
        , api::Mutex() {
        bool_t const isConstructed{ construct() };
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    ~Mutex() noexcept override
    {
        ::DeleteCriticalSection(pcs_);
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override ///< SCA AUTOSAR-C++14 Defected Rule A10-2-1
    {
        return Parent::isConstructed();
    }
    
    /**
     * @copydoc eoos::api::Mutex::tryLock()
     */
    bool_t tryLock() noexcept override try
    {
        bool_t res{ false };
        if( isConstructed() )
        {
            res = ::TryEnterCriticalSection(pcs_) != 0;
        }
        return res;
    } catch (...) {
        return false;
    }    

    /**
     * @copydoc eoos::api::Mutex::lock()
     */
    bool_t lock() noexcept override try
    {
        bool_t res{ false };
        if( isConstructed() )
        {
            ::EnterCriticalSection(pcs_);
            res = true;
        }
        return res;
    } catch (...) {
        return false;
    }

    /**
     * @copydoc eoos::api::Mutex::unlock()
     */
    void unlock() noexcept override try
    {
        if( isConstructed() )
        {
            ::LeaveCriticalSection(pcs_);
        }
    } catch (...) {
        return;
    }

private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct() const noexcept try
    {
        bool_t res{ false };
        while(true)
        {   
            if( !isConstructed() )
            {
                break;
            }
            ::DWORD const spinCount{ 4000U };
            ::BOOL const isInitialize{ ::InitializeCriticalSectionAndSpinCount(pcs_, spinCount) };
            if(isInitialize == 0)
            {
                break;
            }
            res = true;
            break;
        }
        return res;
    } catch (...) {
        return false;
    }
    
    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    Mutex(Mutex const&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    Mutex& operator=(Mutex const&) noexcept = delete;   

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    Mutex(Mutex&&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    Mutex& operator=(Mutex&&) & noexcept = delete;        

    /**
     * @brief Windows critical section object.
     */    
	::CRITICAL_SECTION cs_{};    

    /**
     * @brief Pointer to Windows critical section object.
     */    
	::LPCRITICAL_SECTION const pcs_{ &cs_ };    

};

} // namespace sys
} // namespace eoos
#endif // SYS_MUTEX_HPP_
