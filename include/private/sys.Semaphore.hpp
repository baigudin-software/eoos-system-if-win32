/**
 * @file      sys.Semaphore.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SEMAPHORE_HPP_
#define SYS_SEMAPHORE_HPP_

#include "sys.NonCopyable.hpp"
#include "api.SysSemaphore.hpp"

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
    Semaphore(int32_t permits) try : Parent()
    {
        bool_t const isConstructed = construct(permits);
        setConstructed( isConstructed );
    } catch (...) {
        setConstructed(false);
    }
    
    /**
     * @brief Destructor.
     */
    ~Semaphore() override
    {
        if(handle_ != NULLPTR)
        {
            handle_ = NULLPTR;            
            static_cast<void>( ::CloseHandle(handle_) );
        }
        
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const override
    {
        return Parent::isConstructed();
    }

    /**
     * @copydoc eoos::api::Semaphore::acquire()
     */
    bool_t acquire() override try
    {
        bool_t res {false};
        if( isConstructed() ) 
        {
            ::DWORD error {::WaitForSingleObject(handle_, INFINITE)};
            res = (error == WAIT_OBJECT_0);
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
    bool_t construct(int32_t permits)
    {
        bool_t res {false};
        do {
            if( not isConstructed() )
            {
                break;
            }
            if( permits < 0 || permits > static_cast<int32_t>(MAXIMUM_COUNT) )
            {
                break;
            }
            ::LPSECURITY_ATTRIBUTES const lpSemaphoreAttributes {NULL};
            ::LONG const lInitialCount {permits};
            ::LONG const lMaximumCount {MAXIMUM_COUNT};
            ::LPCSTR lpName {NULL};
            ::HANDLE const handle = ::CreateSemaphore(
                lpSemaphoreAttributes,
                lInitialCount,
                lMaximumCount,
                lpName
            );
            if(handle == NULLPTR)
            {
                break;
            }
            handle_ = handle;
            res = true;
        } while(false);
        return res;
    }
    
    /**
     * @brief Releases the given number of permits.
     *
     * The function releases from the permits and returns these to the semaphore.
     *
     * @param permits The number of permits to release.
     */
    void release(int32_t permits)
    {
        ::LONG const lReleaseCount { static_cast<::LONG>(permits) };
        static_cast<void>( ::ReleaseSemaphore(handle_, lReleaseCount, NULL) );
    }

    /**
     * @brief Maximum Semaphore count.
     */
    static const ::LONG MAXIMUM_COUNT { 0x7FFFFFFF };

    /**
     * @brief A Windows handle of this thread.
     */
    ::HANDLE handle_ {NULLPTR};

};
        
} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHORE_HPP_
