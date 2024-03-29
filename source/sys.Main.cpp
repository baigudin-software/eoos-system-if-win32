/**
 * @file      sys.Main.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2018-2022, Sergey Baigudin, Baigudin Software
 */
#include "sys.System.hpp"

/**
 * @brief The main function.
 *
 * The following tasks must be done before the function called:
 * 1. Stack has been set.
 * 2. CPU registers have been set.
 * 3. Run-time initialization has been completed.
 * 4. Global variables have been set.
 * 5. Global constructors have been called.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv An array of c-string of arguments where the last one - argc + 1 is null. 
 * @return error code or zero.
 */
int main(int argc, char** argv) try ///< SCA AUTOSAR-C++14 Justified Rule A8-4-8
{
    ::eoos::sys::System eoos;
    ::eoos::int32_t const error{ eoos.execute(static_cast<eoos::int32_t>(argc), argv) };
    return static_cast<int>(error); ///< SCA AUTOSAR-C++14 Justified Rule A3-9-1
} 
catch (...) 
{
    // Handle unexpected exceptions following MISRA-C++:2008 Rule 15–3–2 and AUTOSAR-C++14 Rule A15-3-2
    return static_cast<int>(::eoos::sys::Error::UNDEFINED); ///< SCA AUTOSAR-C++14 Justified Rule A3-9-1
}
