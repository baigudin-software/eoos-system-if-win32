/**
 * @file      sys.Semaphore.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2023, Sergey Baigudin, Baigudin Software
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
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class Semaphore : public NonCopyable<A>, public api::Semaphore
{
    using Parent = NonCopyable<A>;

public:

    /**
     * @brief Constructor.
     *
     * @param permits The initial number of permits available.
     */
    explicit Semaphore(int32_t permits) noexcept;
    
    /**
     * @brief Destructor.
     */
    ~Semaphore() noexcept override;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override;

    /**
     * @copydoc eoos::api::Semaphore::acquire()
     */
    bool_t acquire() noexcept override;

    /**
     * @copydoc eoos::api::Semaphore::release()
     */
    void release() noexcept override;

private:

    /**
     * @brief Constructor.
     *
     * @param permits The initial number of permits available.
     * @return true if object has been constructed successfully.
     */
    bool_t construct(int32_t permits) noexcept;
	
    /**
     * @brief Releases the given number of permits.
     *
     * The function releases from the permits and returns these to the semaphore.
     *
     * @param permits The number of permits to release.
     */
    void release(int32_t permits) const;	

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
    Semaphore& operator=(Semaphore&&) & noexcept = delete;        

    /**
     * @brief Maximum Semaphore count.
     */
    static const ::LONG MAXIMUM_COUNT{ 0x7FFFFFFF };

    /**
     * @brief A Windows handle of this thread.
     */
    ::HANDLE handle_{ NULLPTR };

};

template <class A>
Semaphore<A>::Semaphore(int32_t permits) noexcept 
    : NonCopyable<A>()
    , api::Semaphore() {
    bool_t const isConstructed{ construct(permits) };
    setConstructed( isConstructed );
}

template <class A>
Semaphore<A>::~Semaphore() noexcept
{
    if(handle_ != NULLPTR)
    {
        static_cast<void>( ::CloseHandle(handle_) );
        handle_ = NULLPTR;            
    }
}

template <class A>
bool_t Semaphore<A>::isConstructed() const noexcept
{
    return Parent::isConstructed();
}

template <class A>
bool_t Semaphore<A>::acquire() noexcept try
{
    bool_t res{ false };
    if( isConstructed() ) 
    {
        ::DWORD error{ ::WaitForSingleObject(handle_, INFINITE) };
        res = ( error == static_cast< ::DWORD >(WAIT_OBJECT_0) );
    }
    return res;
} catch (...) { ///< UT Justified Branch: OS dependency
    return false;
}

template <class A>
void Semaphore<A>::release() noexcept try
{
    if( isConstructed() )
    {
        release(1);
    }
} catch (...) { ///< UT Justified Branch: OS dependency
    return;
}

template <class A>
bool_t Semaphore<A>::construct(int32_t permits) noexcept try
{
    bool_t res{ false };
    while(true)
    {
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
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
        {   ///< UT Justified Branch: SCA dependency
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
        {   ///< UT Justified Branch: OS dependency
            break;
        }
        handle_ = handle;
        res = true;
        break;
    } ///< UT Justified Line: Compiler dependency
    return res;
}  catch (...) { ///< UT Justified Branch: OS dependency
    return false;
}

template <class A>
void Semaphore<A>::release(int32_t permits) const ///< SCA AUTOSAR-C++14 Justified Rule M9-3-3
{
    ::LONG const lReleaseCount{ static_cast< ::LONG >(permits) };
    static_cast<void>( ::ReleaseSemaphore(handle_, lReleaseCount, NULL) );
}
        
} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHORE_HPP_
