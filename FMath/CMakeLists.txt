cmake_minimum_required(VERSION 3.16)

set(FMATH_VERSION_MAJOR 1)
set(FMATH_VERSION_MINOR 0)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MathConfig.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/MathConfig.h)

add_library(FMath SHARED
            FMath.cpp
           )

target_include_directories(FMath PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_CURRENT_BINARY_DIR}
                          )

target_compile_definitions(FMath PRIVATE BUILDING_FMATH_SHARED)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MathConfig.h DESTINATION include)