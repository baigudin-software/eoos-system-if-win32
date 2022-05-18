/**
 * @file      sys.Thread.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_THREAD_HPP_
#define SYS_THREAD_HPP_

#include "sys.NonCopyable.hpp"
#include "api.Thread.hpp"
#include "api.Task.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Thread
 * @brief Thread class.
 */
class Thread : public NonCopyable, public api::Thread
{
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor of not constructed object.
     *
     * @param task      A task interface whose main function is invoked when this thread is started.
     */
    Thread(api::Task& task) try 
        : NonCopyable()
        , api::Thread()
        , task_(&task){
        bool_t const isConstructed  { construct() };
        setConstructed( isConstructed );
    } catch (...) {
        setConstructed(false);
    }

    /**
     * @brief Destructor.
     */
    ~Thread() override
    {
        if(handle_ != NULLPTR)
        {
            status_ = STATUS_DEAD;            
            handle_ = NULLPTR;
            // @todo The handle closing means the thread will stay in detached mode.
            // Thus, to keep compatibility, common approach for all OSs shall be found.
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
     * @copydoc eoos::api::Thread::execute()
     */
    bool_t execute() override try
    {
        bool_t res {false};
        if( isConstructed() && status_ == STATUS_NEW)
        {
            ::DWORD const exitCode = ::ResumeThread(handle_);
            // If the exitCode is 1, the specified thread was suspended but was restarted.
            if(exitCode == 1)
            {
                status_ = STATUS_RUNNABLE;
                res = true;
            }
            else
            {
                status_ = STATUS_DEAD;
            }
        }
        return res;
    } catch (...) {
        status_ = STATUS_DEAD;
        return false;
    }
    
    /**
     * @copydoc eoos::api::Thread::join()
     */
    bool_t join() override try
    {
        bool_t res {false};
	    if( isConstructed() )
        {
            ::DWORD const error { ::WaitForSingleObject(handle_, INFINITE) };
            res = (error == 0) ? true : false;
            status_ = STATUS_DEAD;
        }
        return res;
    } catch (...) {
        return false;
    }

    /**
     * @copydoc eoos::api::Thread::getPriority()
     */
    int32_t getPriority() const override
    {
        return isConstructed() ? priority_ : PRIORITY_WRONG;        
    }

    /**
     * @copydoc eoos::api::Thread::setPriority(int32_t)
     */
    bool_t setPriority(int32_t priority) override
    {
        bool_t res { false };
        if( isConstructed() )
        {
            if( (PRIORITY_MIN <= priority) && (priority <= PRIORITY_MAX) )
            {
                priority_ = priority;
                res = true;
            }
            else if (priority == PRIORITY_LOCK)
            {
                priority_ = priority;
                res = true;
            }
            else 
            {
                res = false;
            }
        }
        // @todo Implemet setting priority on system level regarding common API rage
        return res;
    }

private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct()
    {  
        bool_t res {false};
        do
        {
            if( !isConstructed() )
            {
                break;
            }
            if( task_ == NULLPTR )
            {
                break;
            }
            if( !task_->isConstructed() )
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
            size_t const stackSize { task_->getStackSize() };
            ::SIZE_T const dwStackSize { static_cast<SIZE_T>(stackSize) };
            
            // A pointer to the application-defined function to be executed by the thread. 
            // This pointer represents the starting address of the thread. 
            // For more information on the thread function, see ThreadProc.
            ::LPTHREAD_START_ROUTINE const lpStartAddress {start};
            
            // A pointer to a variable to be passed to the thread.
            ::LPVOID const lpParameter {&task_};
            
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
            if(handle == NULLPTR)
            {
                break;
            }
            status_ = STATUS_NEW;
            handle_ = handle;
            res = true;
        } while(false);
        if( res == false )
        {
            status_ = STATUS_DEAD;
        }
        return res;    
    }

    /**
     * @brief Runs a function of Runnable interface start vector.
     *
     * @param argument Thread arguments.
     * @return Thread execution resualt.
     */
    static ::DWORD start(::LPVOID argument) try
    {
        int32_t error {-1};
        if(argument != NULLPTR)
        {
            api::Task* const task { *reinterpret_cast<api::Task**>(argument) };
            if(task != NULLPTR)
            {
                if(task->isConstructed())
                {
                    task->start();
                    error = 0;
                }
            }
        }        
        return static_cast<::DWORD>(error);
    } catch (...) {
        return static_cast<::DWORD>(-1);
    }
    
    /**
     * @brief The thread is created in a suspended state, and does not run until the ResumeThread function is called.
     */
    static const ::DWORD WIN32_CREATE_SUSPENDED { 0x00000004 };

    /**
     * @brief The dwStackSize parameter specifies the initial reserve size of the stack. 
     * 
     * If this flag is not specified, dwStackSize specifies the commit size.
     */    
    static const ::DWORD WIN32_STACK_SIZE_PARAM_IS_A_RESERVATION { 0x00010000 };

    /**
     * @brief User executing runnable interface.
     */
    api::Task* task_ {NULLPTR};

    /**
     * @brief Current status.
     */
    Status status_ {STATUS_NEW};
    
    /**
     * @brief This thread priority.
     */    
    int32_t priority_ {PRIORITY_NORM};    

    /**
     * @brief Current identifier.
     */
    ::DWORD id_ {0};
    
    /**
     * @brief A Windows handle of this thread.
     */
    ::HANDLE handle_ {NULLPTR};

};

} // namespace sys
} // namespace eoos
#endif // SYS_THREAD_HPP_
