/**
 * @file      sys.StreamManager.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_STREAMMANAGER_HPP_
#define SYS_STREAMMANAGER_HPP_

#include "sys.NonCopyable.hpp"
#include "api.StreamManager.hpp"
#include "sys.OutStreamChar.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class StreamManager.
 * @brief Stream sub-system manager.
 */
class StreamManager : public NonCopyable, public api::StreamManager
{
    using Parent = NonCopyable;

public:

    /**
     * @brief Constructor.
     */
    StreamManager() noexcept 
        : NonCopyable()
        , api::StreamManager() {
        setConstructed( true );
    }

    /**
     * @brief Destructor.
     */
    ~StreamManager() noexcept override
    {
        cout_.flush();
        cerr_.flush();        
    }

    /**
     * @copydoc eoos::api::Object::isConstructed()
     */
    bool_t isConstructed() const noexcept override
    {
        return Parent::isConstructed();
    }
    
    /**
     * @copydoc eoos::api::StreamManager::getCout()
     */    
    api::OutStream<char_t>& getCout() noexcept override
    {
        return cout_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
    }
    
    /**
     * @copydoc eoos::api::StreamManager::getCerr()
     */
    api::OutStream<char_t>& getCerr() noexcept override
    {
        return cerr_; ///< SCA AUTOSAR-C++14 Justified Rule A9-3-1
    }    

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
    OutStreamChar cout_{OutStreamChar::Type::COUT};

    /**
     * @brief The system error character stream.
     */
    OutStreamChar cerr_{OutStreamChar::Type::CERR};    

};

} // namespace sys
} // namespace eoos
#endif // SYS_STREAMMANAGER_HPP_
