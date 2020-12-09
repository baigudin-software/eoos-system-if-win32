/**
 * @brief Hardware interrupt resource.
 *
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2014-2020, Sergey Baigudin, Baigudin Software
 */
#include "sys.Interrupt.hpp"

namespace eoos
{
namespace sys
{
    
Interrupt::Interrupt(api::Task& handler, int32_t source) : Parent()
{
    bool_t const isConstructed = construct(&handler, source);
    setConstructed( isConstructed );
}

Interrupt::~Interrupt()
{
}

bool_t Interrupt::construct(api::Task* handler, int32_t source)
{
    if( not Self::isConstructed() ) return false;
    return true;
}

bool_t Interrupt::isConstructed() const
{
    return Parent::isConstructed();
}

void Interrupt::jump()
{
}

void Interrupt::clear()
{
}

void Interrupt::set()
{
}

bool_t Interrupt::disable()
{
    return false;
}

void Interrupt::enable(bool_t status)
{
}

bool_t Interrupt::disableAll()
{
    return false;
}

void Interrupt::enableAll(bool_t status)
{
}

} // namespace sys
} // namespace eoos
