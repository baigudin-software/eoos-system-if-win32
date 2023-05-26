/**
 * @file      sys.OutStream.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022-2023, Sergey Baigudin, Baigudin Software
 */
#include "sys.OutStream.hpp"
#include "lib.Memory.hpp"
#include "lib.BaseString.hpp"

namespace eoos
{
namespace sys
{

OutStream::OutStream(Type type) noexcept 
    : NonCopyable<NoAllocator>()
    , api::OutStream<char_t>()
    , type_( type ) 
    , handle_( NULLPTR )
    , lpConsoleScreenBufferInfo_(){
    bool_t const isConstructed{ construct() };
    setConstructed( isConstructed );
}

OutStream::~OutStream() noexcept
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

bool_t OutStream::isConstructed() const noexcept
{
    return Parent::isConstructed();
}

api::OutStream<char_t>& OutStream::operator<<(char_t const* source) noexcept
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

api::OutStream<char_t>& OutStream::operator<<(int32_t value) noexcept
{
    lib::BaseString<char_t,16> str(value);
    return this->operator<<( str.getChar() );
}

api::OutStream<char_t>& OutStream::flush() noexcept
{
    if( isConstructed() )
    {        
        flushStream();
    }
    return *this;
}

bool_t OutStream::construct() noexcept try
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
    
void OutStream::flushStream() const
{
    static_cast<void>( ::FlushConsoleInputBuffer(handle_) );
}    

} // namespace sys
} // namespace eoos
