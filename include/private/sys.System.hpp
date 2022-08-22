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
#include "sys.Configuration.hpp"
#include "sys.Heap.hpp"
#include "sys.OutStreamChar.hpp"
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
     * @copydoc eoos::api::System::getHeap()
     */
    api::Heap& getHeap() override;
    
    /**
     * @copydoc eoos::api::System::getOutStreamChar()
     */    
    api::OutStream<char_t>& getOutStreamChar() override;

    /**
     * @copydoc eoos::api::System::getErrorStreamChar()
     */    
    api::OutStream<char_t>& getErrorStreamChar() override;

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
    int32_t execute() const;
    
    /**
     * @brief Executes the operating system.
     *
     * @param argc The number of arguments passed to the program.
     * @param argv An array of c-string of arguments where the last one - argc + 1 is null.  
     * @return Zero, or error code if the execution has been terminated.
     */
    int32_t execute(int32_t argc, char_t* argv[]) const; ///< SCA AUTOSAR-C++14 Justified Rule A8-4-8
    
    /**
     * @brief Returns an only one created instance of the EOOS system.
     *
     * @return The EOOS system instance.
     */
    static api::System& getSystem();

private:

    /**
     * @brief Constructs this object.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct();
    
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
     * @brief The operating system scheduler.
     */
    Configuration configuration_{};

    /**
     * @brief The operating system scheduler.
     */
    mutable Scheduler scheduler_{};
    
    /**
     * @brief The system heap.
     */
    mutable Heap heap_{}; 

    /**
     * @brief The system output character stream.
     */
    OutStreamChar cout_{OutStreamChar::Type::COUT};

    /**
     * @brief The system error character stream.
     */
    OutStreamChar cerr_{OutStreamChar::Type::CERR};

};

} // namespace sys
} // namespace eoos
#endif // SYS_SYSTEM_HPP_
