/**
 * @file      sys.Configuration.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2016-2022, Sergey Baigudin, Baigudin Software
 */
#include "sys.Configuration.hpp"

namespace eoos
{
namespace sys
{

Configuration::Configuration()
    : heapSize    (0x00001000)
    , stackSize   (0x00000800) {
}

} // namespace sys
} // namespace eoos
