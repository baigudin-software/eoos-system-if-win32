/**
 * @file      sys.System.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_SYSTEM_HPP_
#define SYS_SYSTEM_HPP_

#include "sys.NonCopyable.hpp"
#include "api.System.hpp"
#include "sys.Scheduler.hpp"
#include "sys.MutexManager.hpp"
#include "sys.SemaphoreManager.hpp"
#include "sys.StreamManager.hpp"
#include "sys.Heap.hpp"
#include "sys.Error.hpp"

namespace eoos
{
namespace sys
{
    
/**
 * @class System
 * @brief The operating system.
 */
class System : public NonCopyable<NoAllocator>, public api::System
{
    using Parent = NonCopyable<NoAllocator>;

public:

    /**
     * @brief Constructor.
     */
    System() noexcept;

    /**
     * @brief Destructor.
     */
    ~System() noexcept override;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override; ///< SCA AUTOSAR-C++14 Defected Rule A10-2-1
    
    /**
     * @copydoc eoos::api::System::getHeap()
     */
    api::Heap& getHeap() noexcept override;

    /**
     * @copydoc eoos::api::System::getScheduler()
     */
    api::Scheduler& getScheduler() noexcept override;    
    
    /**
     * @copydoc eoos::api::System::hasMutexManager()
     */
    bool_t hasMutexManager() noexcept override;

    /**
     * @copydoc eoos::api::System::getMutexManager()
     */
    api::MutexManager& getMutexManager() noexcept override;

    /**
     * @copydoc eoos::api::System::hasSemaphoreManager()
     */
    bool_t hasSemaphoreManager() noexcept override;

    /**
     * @copydoc eoos::api::System::getSemaphoreManager()
     */
    api::SemaphoreManager& getSemaphoreManager() noexcept override;
    
    /**
     * @copydoc eoos::api::System::hasStreamManager()
     */
    bool_t hasStreamManager() noexcept override;

    /**
     * @copydoc eoos::api::System::getStreamManager()
     */
    api::StreamManager& getStreamManager() noexcept override;

    /**
     * @brief Executes the operating system.
     *
     * @return Zero, or error code if the execution has been terminated.
     */
    int32_t execute() const noexcept;
    
    /**
     * @brief Executes the operating system.
     *
     * @param argc The number of arguments passed to the program.
     * @param argv An array of c-string of arguments where the last one - argc + 1 is null.  
     * @return Zero, or error code if the execution has been terminated.
     */
    int32_t execute(int32_t argc, char_t* argv[]) const noexcept; ///< SCA AUTOSAR-C++14 Justified Rule A8-4-8
    
    /**
     * @brief Returns an only one created instance of the EOOS system.
     *
     * @return The EOOS system instance.
     */
    static api::System& getSystem() noexcept;

private:

    /**
     * @brief Constructs this object.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct() noexcept;
    
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
    System& operator=(System&&) & noexcept = delete;    
    
    /**
     * @brief Terminates the system execution.
     *
     * @param Error an exit code.
     */
    static void exit(Error error);

    /**
     * @brief The operating system.
     */
    static api::System* eoos_;

    /**
     * @brief The system heap.
     */
    Heap heap_{};    

    /**
     * @brief The operating system scheduler.
     */
    Scheduler scheduler_{};

    /**
     * @brief The mutex sub-system manager.
     */
    MutexManager mutex_{};

    /**
     * @brief The semaphore sub-system manager.
     */
    SemaphoreManager semaphore_{};
    
    /**
     * @brief The stream sub-system manager.
     */
    StreamManager stream_{};

};

} // namespace sys
} // namespace eoos
#endif // SYS_SYSTEM_HPP_
