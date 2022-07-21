/**
 * @file      sys.Semaphore.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHORE_HPP_
#define SYS_SEMAPHORE_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Semaphore.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Semaphore
 * @brief Semaphore class.
 */
class Semaphore : public NonCopyable, public api::Semaphore
{
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     *
     * @param permits The initial number of permits available.
     */
    explicit Semaphore(int32_t permits) 
        : NonCopyable()
        , api::Semaphore() {
        bool_t const isConstructed{ construct(permits) };
        setConstructed( isConstructed );
    }
    
    /**
     * @brief Destructor.
     */
    ~Semaphore() override
    {
        if(handle_ != NULLPTR)
        {
            static_cast<void>( ::CloseHandle(handle_) );
            handle_ = NULLPTR;            
        }
        
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const override ///< SCA AUTOSAR-C++14 Defected Rule A10-2-1
    {
        return Parent::isConstructed();
    }

    /**
     * @copydoc eoos::api::Semaphore::acquire()
     */
    bool_t acquire() override try
    {
        bool_t res{ false };
        if( isConstructed() ) 
        {
            ::DWORD error{ ::WaitForSingleObject(handle_, INFINITE) };
            res = ( error == static_cast< ::DWORD >(WAIT_OBJECT_0) );
        }
        return res;
    } catch (...) {
        return false;
    }

    /**
     * @copydoc eoos::api::Semaphore::release()
     */
    void release() override try
    {
        if( isConstructed() )
        {
            release(1);
        }
    } catch (...) {
        return;
    }


private:

    /**
     * @brief Constructor.
     *
     * @param permits The initial number of permits available.
     * @return true if object has been constructed successfully.
     */
    bool_t construct(int32_t permits) try
    {
        bool_t res{ false };
        while(true)
        {
            if( !isConstructed() )
            {
                break;
            }
            if( permits < 0 )
            {
                break;
            }
            // To comply SCA AUTOSAR-C++14 M0-1-2 and to check permits is not more than MAXIMUM_COUNT 
            // if the maximum would be changed, the values are explicitly casted to int64_t.
            // Thus, if MAXIMUM_COUNT would be less than 0x7FFFFFFF, we have to cast to int32_t back.
            if( static_cast<int64_t>(permits) > static_cast<int64_t>(MAXIMUM_COUNT) )
            {
                break;
            }            
            ::LPSECURITY_ATTRIBUTES const lpSemaphoreAttributes{ NULL };
            ::LONG const lInitialCount{ permits };
            ::LONG const lMaximumCount{ MAXIMUM_COUNT };
            ::LPCSTR lpName{ NULL };
            ::HANDLE const handle{ ::CreateSemaphore(
                lpSemaphoreAttributes,
                lInitialCount,
                lMaximumCount,
                lpName
            ) };
            if(handle == NULLPTR)
            {
                break;
            }
            handle_ = handle;
            res = true;
            break;
        }
        return res;
    }  catch (...) {
        return false;
    }

    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    Semaphore(Semaphore const&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    Semaphore& operator=(Semaphore const&) noexcept = delete;   

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    Semaphore(Semaphore&&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    Semaphore& operator=(Semaphore&&) noexcept = delete;        
    
    /**
     * @brief Releases the given number of permits.
     *
     * The function releases from the permits and returns these to the semaphore.
     *
     * @param permits The number of permits to release.
     */
    void release(int32_t permits) ///< SCA AUTOSAR-C++14 Justified Rule M9-3-3
    {
        ::LONG const lReleaseCount{ static_cast< ::LONG >(permits) };
        static_cast<void>( ::ReleaseSemaphore(handle_, lReleaseCount, NULL) );
    }

    /**
     * @brief Maximum Semaphore count.
     */
    static const ::LONG MAXIMUM_COUNT{ 0x7FFFFFFF };

    /**
     * @brief A Windows handle of this thread.
     */
    ::HANDLE handle_{ NULLPTR };

};
        
} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHORE_HPP_
