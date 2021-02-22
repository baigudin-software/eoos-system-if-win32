/**
 * @brief Mutex.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_MUTEX_HPP_
#define SYS_MUTEX_HPP_

#include "sys.NonCopyable.hpp"
#include "api.SysMutex.hpp"

#include <Windows.h>

namespace eoos
{
namespace sys
{

/**
 * @brief Mutex class.
 */
class Mutex : public NonCopyable, public api::Mutex
{
    using Self = Mutex;
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    Mutex() noexcept : Parent()
    {
        bool_t const isConstructed = construct();
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
     * @brief Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t isConstructed() const noexcept override 
    {
        return Parent::isConstructed();
    }
    
    /**
     * @brief Tries to locks this mutex.
     *
     * @return true if this mutex is locked successfully, or false if other thread locked on this mutex.
     */
    bool_t tryLock() noexcept override try
    {
        bool_t res {false};
        if( Self::isConstructed() )
        {
            res = ::TryEnterCriticalSection(pcs_) != 0;
        }
        return res;
    } catch (...) {
        return false;
    }    

    /**
     * @brief Locks the mutex.
     *
     * @return true if the mutex is lock successfully.
     */
    bool_t lock() noexcept override try
    {
        bool_t res {false};
        if( not Self::isConstructed() )
        {
            ::EnterCriticalSection(pcs_);
            res = true;
        }
        return res;
    } catch (...) {
        return false;
    }

    /**
     * @brief Unlocks the mutex.
     */
    void unlock() noexcept override try
    {
        if( not Self::isConstructed() )
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
     * @return true if object has been constructed successfully.
     */
    bool_t construct() noexcept try
    {
        bool_t res = false;
        do
        {   
            if( not Self::isConstructed() )
            {
                break;
            }
            ::DWORD const spinCount = 4000;
            ::BOOL const isInitialize = ::InitializeCriticalSectionAndSpinCount(pcs_, spinCount);
            if(isInitialize == 0)
            {
                break;
            }
            res = true;
        } while(false);
        return res;
    } catch (...) {
        return false;
    }

    /**
     * @brief Windows critical section object.
     */    
	::CRITICAL_SECTION cs_;    

    /**
     * @brief Pointer to Windows critical section object.
     */    
	::LPCRITICAL_SECTION const pcs_ {&cs_};    

};

} // namespace sys
} // namespace eoos
#endif // SYS_MUTEX_HPP_
