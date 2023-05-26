/**
 * @file      sys.OutStream.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2022-2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_OUTSTREAM_HPP_
#define SYS_OUTSTREAM_HPP_

#include "sys.NonCopyable.hpp"
#include "api.OutStream.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class OutStream.
 * @brief OutStream class.
 */
class OutStream : public NonCopyable<NoAllocator>, public api::OutStream<char_t>
{
    using Parent = NonCopyable<NoAllocator>;

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
    OutStream(Type type) noexcept;

    /**
     * @brief Destructor.
     */
    ~OutStream() noexcept override;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override;
    
    /**
     * @copydoc eoos::api::OutStream::operator<<(T const*)
     */
    api::OutStream<char_t>& operator<<(char_t const* source) noexcept override;

    /**
     * @copydoc eoos::api::OutStream::operator<<(int32_t)
     */
    api::OutStream<char_t>& operator<<(int32_t value) noexcept override;

    /**
     * @copydoc eoos::api::OutStream::flush()
     */    
    api::OutStream<char_t>& flush() noexcept override;
    
private:

    /**
     * @brief Constructor.
     *
     * @return True if object has been constructed successfully.
     */
    bool_t construct() noexcept;
    
    /**
     * @brief Flushs stream.
     */    
    void flushStream() const;
    
    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    OutStream(OutStream const&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    OutStream& operator=(OutStream const&) noexcept = delete;   

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    OutStream(OutStream&&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    OutStream& operator=(OutStream&&) & noexcept = delete;
    
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
#endif // SYS_OUTSTREAM_HPP_
