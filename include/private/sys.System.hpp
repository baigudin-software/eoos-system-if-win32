/**
 * @file      sys.System.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SYSTEM_HPP_
#define SYS_SYSTEM_HPP_

#include "sys.NonCopyable.hpp"
#include "api.System.hpp"
#include "sys.Scheduler.hpp"
#include "sys.Error.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @class System
 * @brief The operating system.
 */
class System : public NonCopyable, public api::System
{
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    System();

    /**
     * @brief Destructor.
     */
    ~System() override;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const override; ///< SCA AUTOSAR-C++14 Defected Rule A10-2-1

    /**
     * @copydoc eoos::api::System::getScheduler()
     */
    api::Scheduler& getScheduler() override;

    /**
     * @copydoc eoos::api::System::createMutex()
     */
    api::Mutex* createMutex() override;

    /**
     * @copydoc eoos::api::System::creatSemaphore(int32_t)
     */
    api::Semaphore* createSemaphore(int32_t permits) override;

    /**
     * @brief Executes the operating system.
     *
     * @return Zero, or error code if the execution has been terminated.
     */
    int32_t execute();
    
    /**
     * @brief Terminates the system execution.
     *
     * @param Error an exit code.
     */
    static void exit(Error error);    

private:

    /**
     * @brief Constructs this object.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct() const;
    
    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    System(System const&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    System& operator=(System const&) noexcept = delete;   

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    System(System&&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    System& operator=(System&&) noexcept = delete;

    /**
     * @brief The operating system initialization flag.
     */
    static bool_t isInitialized_;

    /**
     * @brief The operating system scheduler.
     */
    mutable Scheduler scheduler_{};

};

} // namespace sys
} // namespace eoos
#endif // SYS_SYSTEM_HPP_
