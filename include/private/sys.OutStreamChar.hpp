/**
 * @file      sys.OutStreamChar.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OUTSTREAMCHAR_HPP_
#define SYS_OUTSTREAMCHAR_HPP_

#include "sys.NonCopyable.hpp"
#include "api.OutStream.hpp"
#include "lib.Memory.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class OutStreamChar.
 * @brief OutStreamChar class.
 */
class OutStreamChar : public NonCopyable, public api::OutStream<char_t>
{
    using Parent = NonCopyable;

public:

    /**
     * @class Type.
     * @brief Type output.
     */
    enum class Type : int32_t
    {
        COUT, ///< @brief COUT
        CERR  ///< @brief CERR
    };

    /**
     * @brief Constructor.
     *
     * @param type Type output.
     */
    OutStreamChar(Type type) noexcept 
        : NonCopyable()
        , api::OutStream<char_t>()
        , type_( type ) 
        , handle_( NULLPTR )
        , lpConsoleScreenBufferInfo_(){
        bool_t const isConstructed{ construct() };
        setConstructed( isConstructed );
    }

    /**
     * @brief Destructor.
     */
    ~OutStreamChar() noexcept override
    {
        if(handle_ != NULLPTR)
        {
            // It is not required to CloseHandle when done with the handle retrieved from GetStdHandle. 
            // The returned value is simply a copy of the value stored in the process table.
            // Moreover, closing the handle will lead to stop outputting if EOOS instance 
            // will be deleted and created again.
            flushStream();
            handle_ = NULLPTR;            
        }        
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override ///< SCA AUTOSAR-C++14 Defected Rule A10-2-1
    {
        return Parent::isConstructed();
    }
    
    /**
     * @copydoc eoos::api::OutStream::operator<<()
     */
    OutStream<char_t>& operator<<(char_t const* source) noexcept override
    {
        if( isConstructed() )
        {
            ::WORD wAttributes( lpConsoleScreenBufferInfo_.wAttributes );
            if(type_ == Type::CERR)
            {
                ::WORD wForegroundMask( FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
                wForegroundMask = ~wForegroundMask;
                wAttributes &= wForegroundMask;
                wAttributes |= FOREGROUND_RED | FOREGROUND_INTENSITY;
            }
            static_cast<void>( ::SetConsoleTextAttribute(handle_, wAttributes) );
            ::DWORD numberOfCharsToWrite( static_cast< ::DWORD >( lib::Memory::strlen(source)) );
            ::DWORD numberOfCharsWritten; ///< SCA AUTOSAR-C++14 Justified Rule M0-1-4
            static_cast<void>( ::WriteConsoleA(handle_, source, numberOfCharsToWrite, &numberOfCharsWritten, NULL) );
            static_cast<void>( ::SetConsoleTextAttribute(handle_, lpConsoleScreenBufferInfo_.wAttributes) );
        }
        return *this;
    }

    /**
     * @copydoc eoos::api::OutStream::flush()
     */    
    OutStream<char_t>& flush() noexcept override
    {
        if( isConstructed() )
        {        
            flushStream();
        }
        return *this;
    }
    
private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct() noexcept try
    {
        bool_t res{ false };
        while(true)
        {   
            if( !isConstructed() )
            {   ///< UT Justified Branch: HW dependency
                break;
            }
            DWORD nStdHandle;
            if(type_ == Type::COUT)
            {
                nStdHandle = STD_OUTPUT_HANDLE;
            }
            else
            {
                nStdHandle = STD_ERROR_HANDLE;
            }
            handle_ = ::GetStdHandle(nStdHandle);
            if( handle_ == INVALID_HANDLE_VALUE ) ///< SCA AUTOSAR-C++14 Justified Rule M5-2-8 and Rule A5-2-2
            {   ///< UT Justified Branch: OS dependency
                break;
            }
            // Don't check on NULL here as:
            // If an application does not have associated standard handles, such as a service running 
            // on an interactive desktop, and has not redirected them, the return value is NULL.
            // Thus, if an output handle is not exist, will flush the stream nowhere.
            ::BOOL isGot( ::GetConsoleScreenBufferInfo(handle_, &lpConsoleScreenBufferInfo_) );
            if( isGot == 0 )
            {   ///< UT Justified Branch: OS dependency
                break;
            }
            res = true;
            break;
        } ///< UT Justified Line: Compiler dependency
        return res;
    } catch (...) { ///< UT Justified Branch: OS dependency
        return false;
    }
    
    /**
     * @brief Flushs stream.
     */    
    void flushStream() const
    {
        static_cast<void>( ::FlushConsoleInputBuffer(handle_) );
    }    
    
    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    OutStreamChar(OutStreamChar const&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    OutStreamChar& operator=(OutStreamChar const&) noexcept = delete;   

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    OutStreamChar(OutStreamChar&&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    OutStreamChar& operator=(OutStreamChar&&) & noexcept = delete;
    
    /**
     * @brief Type of stream.
     */
    Type type_;

    /**
     * @brief A Windows handle of this stream.
     */
    ::HANDLE handle_;

    /**
     * @brief Original console screen buffer information.
     */    
    ::CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo_;

};

} // namespace sys
} // namespace eoos
#endif // SYS_OUTSTREAMCHAR_HPP_
