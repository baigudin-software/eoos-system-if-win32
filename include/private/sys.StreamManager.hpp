/**
 * @file      sys.StreamManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_STREAMMANAGER_HPP_
#define SYS_STREAMMANAGER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.StreamManager.hpp"
#include "sys.OutStream.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class StreamManager.
 * @brief Stream sub-system manager.
 */
class StreamManager : public NonCopyable<NoAllocator>, public api::StreamManager
{
    using Parent = NonCopyable<NoAllocator>;

public:

    /**
     * @brief Constructor.
     */
    StreamManager() noexcept;

    /**
     * @brief Destructor.
     */
    ~StreamManager() noexcept override;

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override;
    
    /**
     * @copydoc eoos::api::StreamManager::getCout()
     */    
    api::OutStream<char_t>& getCout() noexcept override;
    
    /**
     * @copydoc eoos::api::StreamManager::getCerr()
     */
    api::OutStream<char_t>& getCerr() noexcept override;

    /**
     * @copydoc eoos::api::StreamManager::setCout(api::OutStream<char_t>&)
     */
    bool_t setCout(api::OutStream<char_t>& cout) noexcept override;

    /**
     * @copydoc eoos::api::StreamManager::setCerr(api::OutStream<char_t>&)
     */
    bool_t setCerr(api::OutStream<char_t>& cerr) noexcept override;

    /**
     * @copydoc eoos::api::StreamManager::resetCout()
     */
    void resetCout() noexcept override;

    /**
     * @copydoc eoos::api::StreamManager::resetCerr()
     */
    void resetCerr() noexcept override;

private:
    
    /**
     * @copydoc eoos::Object::Object(Object const&)
     */
    StreamManager(StreamManager const&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object const&)
     */       
    StreamManager& operator=(StreamManager const&) noexcept = delete;   

    /**
     * @copydoc eoos::Object::Object(Object&&)
     */       
    StreamManager(StreamManager&&) noexcept = delete;
    
    /**
     * @copydoc eoos::Object::operator=(Object&&)
     */
    StreamManager& operator=(StreamManager&&) & noexcept = delete;
    
    /**
     * @brief The system output character stream.
     */
    OutStream coutDef_{ OutStream::Type::COUT };

    /**
     * @brief The system error character stream.
     */
    OutStream cerrDef_{ OutStream::Type::CERR };
    
    /**
     * @brief The system output character stream.
     */    
    api::OutStream<char_t>* cout_{ &coutDef_ };

    /**
     * @brief The system error character stream.
     */    
    api::OutStream<char_t>* cerr_{ &cerrDef_ };    

};

} // namespace sys
} // namespace eoos
#endif // SYS_STREAMMANAGER_HPP_
