# EOOS SYSTEM.
#
# @author    Sergey Baigudin, sergey@baigudin.software
# @copyright 2019-2020, Sergey Baigudin, Baigudin Software

target_include_directories(target-eoos
PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/private>
)

target_sources(target-eoos
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/source/sys.Allocator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/sys.Heap.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/sys.Interrupt.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/sys.Main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/sys.Object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/sys.Scheduler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/sys.System.cpp
)
