/**
 * @file      sys.Configuration.hpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2022, Sergey Baigudin, Baigudin Software
 */
#ifndef SYS_CONFIGURATION_HPP_
#define SYS_CONFIGURATION_HPP_

#include "Types.hpp"

namespace eoos
{
namespace sys
{

/**
 * @class Configuration
 * @brief The configuration of a target processor.
 */
class Configuration final
{
    
public:

    #ifndef EOOS_GLOBAL_ENABLE_NO_HEAP

    /**
     * @brief Returns size of heap memory in bytes.
     */
    size_t getHeapSize() const
    { 
        return heapSize_;
    }

    #endif // EOOS_GLOBAL_ENABLE_NO_HEAP

    /**
     * @brief Stack size in bytes for the first user thread to be created.
     */
    size_t getStackSize() const
    {
        return stackSize_;
    }
    
private:
    
    #ifndef EOOS_GLOBAL_ENABLE_NO_HEAP

    /**
     * @brief Size of heap memory in bytes.
     */
    size_t heapSize_{ 0x00000000U };

    #endif // EOOS_GLOBAL_ENABLE_NO_HEAP

    /**
     * @brief Stack size in bytes for the first user thread to be created.
     */
    size_t stackSize_{ 0x00000000U };

};

} // namespace sys
} // namespace eoos
#endif // SYS_CONFIGURATION_HPP_
