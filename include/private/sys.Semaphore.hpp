/**
 * @brief Semaphore.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2021, Sergey Baigudin, Baigudin Software
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
 * @brief Semaphore class.
 */
class Semaphore : public NonCopyable, public api::Semaphore
{
    using Self = Semaphore;
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     *
     * @param permits the initial number of permits available.
     */
    Semaphore(int32_t permits) : Parent()
    {
        bool_t const isConstructed = construct(permits);
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    ~Semaphore() override
    {
    }

    /**
     * @brief Tests if this object has been constructed.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t isConstructed() const override
    {
        return Parent::isConstructed();
    }

    /**
     * @brief Acquires one permit from this semaphore.
     *
     * @return true if the semaphore is acquired successfully.
     */
    bool_t acquire() override
    {
        if( not Self::isConstructed() ) return false;
        return false;
    }

    /**
     * @brief Acquires the given number of permits from this semaphore.
     *
     * @param permits The number of permits to acquire.
     * @return true if the semaphore is acquired successfully.
     */
    bool_t acquire(int32_t permits) override
    {
        if( not Self::isConstructed() ) return false;
        return false;
    }

    /**
     * @brief Releases one permit.
     */
    void release() override
    {
        if( not Self::isConstructed() ) return;
    }

    /**
     * @brief Releases the given number of permits.
     *
     * @param permits The number of permits to release.
     */
    void release(int32_t permits) override
    {
        if( not Self::isConstructed() ) return;
    }

    /**
     * @brief Tests if this semaphore is fair.
     *
     * @return true if this semaphore has fairness set true.
     */
    bool_t isFair() const override
    {
        return false;
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
        if( not Self::isConstructed() ) return false;
        return true;
    }

};
        
} // namespace sys
} // namespace eoos
#endif // SYS_SEMAPHORE_HPP_
