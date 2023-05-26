/**
 * @file      sys.Scheduler.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2017-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SCHEDULER_HPP_
#define SYS_SCHEDULER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Scheduler.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Scheduler
 * @brief Thread tasks scheduler class.
 */
class Scheduler : public NonCopyable<NoAllocator>, public api::Scheduler
{
    using Parent = NonCopyable<NoAllocator>;

public:

    /**
     * @brief Constructor.
     */
    Scheduler() noexcept;

    /**
     * @brief Destructor.
     */
    ~Scheduler() noexcept override = default;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override; ///< SCA AUTOSAR-C++14 Defected Rule A10-2-1

    /**
     * @copydoc eoos::api::Scheduler::createThread(api::Task&)
     */     
    api::Thread* createThread(api::Task& task) noexcept override; ///< SCA AUTOSAR-C++14 Justified Rule A8-4-8
    
    /**
     * @copydoc eoos::api::Scheduler::sleep(int32_t)
     */
    bool_t sleep(int32_t ms) noexcept override;

    /**
     * @copydoc eoos::api::Scheduler::yield()
     */
    void yield() noexcept override;

private:

    /**
     * @brief Constructor.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct() noexcept;
    
    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    Scheduler(Scheduler const&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    Scheduler& operator=(Scheduler const&) noexcept = delete;   

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    Scheduler(Scheduler&&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    Scheduler& operator=(Scheduler&&) & noexcept = delete;    
    
    /**
     * @brief A Windows handle of root application process.
     */
    ::HANDLE processHandle_{ NULLPTR };

    /**
     * @brief Priority of the root application process.
     */    
    ::DWORD processPriority_{ 0U };
};

} // namespace sys
} // namespace eoos
#endif // SYS_SCHEDULER_HPP_
