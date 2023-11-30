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
 * 
 * @tparam A Heap memory allocator class.
 */
template <class A>
class Mutex : public NonCopyable<A>, public api::Mutex
{
    using Parent = NonCopyable<A>;

public:

    /**
     * @brief Constructor.
     */
    Mutex() noexcept;

    /**
     * @brief Destructor.
     */
    ~Mutex() noexcept override;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override;
    
    /**
     * @copydoc eoos::api::Mutex::tryLock()
     */
    bool_t tryLock() noexcept override;

    /**
     * @copydoc eoos::api::Mutex::lock()
     */
    bool_t lock() noexcept override;

    /**
     * @copydoc eoos::api::Mutex::unlock()
     */
    bool_t unlock() noexcept override;

private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct() const noexcept;
    
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

template <class A>
Mutex<A>::Mutex() noexcept
    : NonCopyable<A>()
    , api::Mutex() {
    bool_t const isConstructed{ construct() };
    setConstructed( isConstructed );
}

template <class A>
Mutex<A>::~Mutex() noexcept
{
    ::DeleteCriticalSection(pcs_);
}

template <class A>
bool_t Mutex<A>::isConstructed() const noexcept
{
    return Parent::isConstructed();
}

template <class A>
bool_t Mutex<A>::tryLock() noexcept try
{
    bool_t res{ false };
    if( isConstructed() )
    {
        res = ::TryEnterCriticalSection(pcs_) != 0;
    }
    return res;
} catch (...) { ///< UT Justified Branch: OS dependency
    return false;
}    

template <class A>
bool_t Mutex<A>::lock() noexcept try
{
    bool_t res{ false };
    if( isConstructed() )
    {
        ::EnterCriticalSection(pcs_);
        res = true;
    }
    return res;
} catch (...) { ///< UT Justified Branch: OS dependency
    return false;
}

template <class A>
bool_t Mutex<A>::unlock() noexcept try
{
    bool_t res{ false };    
    if( isConstructed() )
    {
        ::LeaveCriticalSection(pcs_);
        res = true;
    }
    return res;
} catch (...) { ///< UT Justified Branch: OS dependency
    return false;
}

template <class A>
bool_t Mutex<A>::construct() const noexcept try
{
    bool_t res{ false };
    while(true)
    {   
        if( !isConstructed() )
        {   ///< UT Justified Branch: HW dependency
            break;
        }
        ::DWORD const spinCount{ 4000U };
        ::BOOL const isInitialize{ ::InitializeCriticalSectionAndSpinCount(pcs_, spinCount) };
        if(isInitialize == 0)
        {   ///< UT Justified Branch: OS dependency
            break;
        }
        res = true;
        break;
    }
    return res;
} catch (...) { ///< UT Justified Branch: OS dependency
    return false;
}

} // namespace sys
} // namespace eoos
#endif // SYS_MUTEX_HPP_
