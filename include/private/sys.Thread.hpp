/**
 * @brief Thread.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2021, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_THREAD_HPP_
#define SYS_THREAD_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Thread.hpp"
#include "api.Task.hpp"

#include <Windows.h>

namespace eoos
{
namespace sys
{

/**
 * @brief Thread class.
 */
class Thread : public NonCopyable, public api::Thread
{
    using Self = Thread;
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor of not constructed object.
     *
     * @param task      A task interface whose main method is invoked when this thread is started.
     * @param scheduler A scheduler controls this thread.
     */
    Thread(api::Task& task, Scheduler* const scheduler) : Parent(),
        task_          (&task),
        scheduler_     (scheduler){
        bool_t const isConstructed  { construct() };
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    ~Thread() override
    {
        if(handle_ != NULL)
        {
            ::CloseHandle(handle_);
        }
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
     * @brief Causes this thread to begin execution.
     */
    void execute() noexcept override try
    {
        if( Self::isConstructed() && status_ == NEW)
        {
            ::DWORD const exitCode = ResumeThread(handle_);
            if(exitCode != -1)
            {
                status_ = RUNNABLE;
            }
            else
            {
                status_ = DEAD;
            }
        }
    } catch (...) {
        status_ = DEAD;
        return;
    }    
    /**
     * @brief Waits for this thread to die.
     */
    void join() noexcept override try
    {
	    if( Self::isConstructed() )
        {
            static_cast<void>( ::WaitForSingleObject(handle_, INFINITE) );
        }
    } catch (...) {
        return;
    }

    /**
     * @brief Returns the identifier of this thread.
     *
     * @return the thread identifier, or -1 if an error has been occurred.
     */
    int64_t getId() const noexcept override
    {
        return Self::isConstructed() ? static_cast<int64_t>(id_) : WRONG_ID;
    }

    /**
     * @brief Returns this thread priority.
     *
     * @return priority value, or -1 if an error has been occurred.
     */
    int32_t getPriority() const noexcept override
    {
        return NORM_PRIORITY;
    }

    /**
     * @brief Sets this thread priority.
     *
     * @param priority number of priority in range [MIN_PRIORITY, MAX_PRIORITY], or LOCK_PRIORITY.
     */
    void setPriority(int32_t priority) noexcept override
    {
    }

    /**
     * @brief Returns a status of this thread.
     *
     * @return this thread status.
     */
    Status getStatus() const noexcept override
    {
        return Self::isConstructed() ? status_ : DEAD;
    }
    
    /**
     * @brief Returns an error of this thread task execution.
     *
     * @return an execution error.
     */
    int32_t getExecutionError() const noexcept override
    {
        return error_;
    }    

private:

    /**
     * @brief Constructor.
     *
     * @return true if object has been constructed successfully.
     */
    bool_t construct() noexcept try
    {  
        bool_t res {false};
        do
        {
            if( not Self::isConstructed() )
            {
                break;
            }
            if( task_ == NULLPTR || scheduler_ == NULLPTR )
            {
                break;
            }
            if( not task_->isConstructed() || not scheduler_->isConstructed() )
            {
                break;
            }
            // A pointer to a SECURITY_ATTRIBUTES structure that determines whether the returned handle 
            // can be inherited by child processes. If lpThreadAttributes is NULL, the handle cannot be inherited.
            // The lpSecurityDescriptor member of the structure specifies a security descriptor for the new thread. 
            // If lpThreadAttributes is NULL, the thread gets a default security descriptor. The ACLs in the default 
            // security descriptor for a thread come from the primary token of the creator.
            ::LPSECURITY_ATTRIBUTES const lpThreadAttributes {NULL};
            
            // The initial size of the stack, in bytes. The system rounds this value to the nearest page. 
            // If this parameter is zero, the new thread uses the default size for the executable. 
            // For more information, see Thread Stack Size.
            int32_t const stackSise { task_->getStackSize() };
            if(stackSise < 0)
            {
                break;
            }
            ::SIZE_T const dwStackSize { static_cast<SIZE_T>(stackSise) };
            
            // A pointer to the application-defined function to be executed by the thread. 
            // This pointer represents the starting address of the thread. 
            // For more information on the thread function, see ThreadProc.
            ::LPTHREAD_START_ROUTINE const lpStartAddress {start};
            
            // A pointer to a variable to be passed to the thread.
            ::LPVOID const lpParameter {&this_};
            
            // The flags that control the creation of the thread.
            // WIN32_CREATE_SUSPENDED to wait, or 0.
            ::DWORD const dwCreationFlags = WIN32_CREATE_SUSPENDED;
            
            // A pointer to a variable that receives the thread identifier. 
            // If this parameter is NULL, the thread identifier is not returned.
            ::LPDWORD lpThreadId = &id_;
            
            ::HANDLE const handle = ::CreateThread(
                lpThreadAttributes, 
                dwStackSize, 
                lpStartAddress, 
                lpParameter, 
                dwCreationFlags, 
                lpThreadId
            );
            if(handle == NULL)
            {
                break;
            }
            handle_ = handle;
            res = true;
        } while(false);
        return res;    
    } catch (...) {
        return false;
    }
    

    /**
     * @brief Runs a method start() of this thread task.
     */
    int32_t run()
    {
        error_ = task_->start();
        status_ = DEAD;
        return error_;
    }

    /**
     * @brief Runs a method of Runnable interface start vector.
     */
    static ::DWORD start(::LPVOID argument) noexcept try
    {
        int32_t error {-1};
        if(argument != NULLPTR)
        {
            Thread* const thread = *reinterpret_cast<Thread**>(argument);
            if(thread != NULLPTR)
            {
                if(thread->isConstructed())
                {
                    // Invoke the member function through the pointer
                    error = thread->run();
                }
            }
        }        
        return static_cast<::DWORD>(error);
    } catch (...) {
        return static_cast<::DWORD>(-1);
    }
    
    /**
     * The thread is created in a suspended state, and does not run until the ResumeThread function is called.
     */
    static const ::DWORD WIN32_CREATE_SUSPENDED { 0x00000004 };

    /**
     * The dwStackSize parameter specifies the initial reserve size of the stack. If this flag is not specified, 
     * dwStackSize specifies the commit size.
     */    
    static const ::DWORD WIN32_STACK_SIZE_PARAM_IS_A_RESERVATION { 0x00010000 };

    /**
     * @brief User executing runnable interface.
     */
    api::Task* task_ {NULLPTR};

    /**
     * @brief The scheduler resource.
     */
    Scheduler* scheduler_ {NULLPTR};

    /**
     * @brief Current status.
     */
    Status status_ {NEW};
    
    /**
     * @brief Error of the thread task executio.
     */    
    int32_t error_ {-1};    

    /**
     * @brief This class pointer.
     */
    Thread* this_ {this};

    /**
     * @brief Current identifier.
     */
    ::DWORD id_ {0};
    
    /**
     * @brief A Windows handle of this thread.
     */
    ::HANDLE handle_ {NULL};

};

} // namespace sys
} // namespace eoos
#endif // SYS_THREAD_HPP_
