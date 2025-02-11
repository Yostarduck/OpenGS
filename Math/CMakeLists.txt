cmake_minimum_required(VERSION 3.16)

set(MATH_VERSION_MAJOR 1)
set(MATH_VERSION_MINOR 0)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gsMathConfig.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/gsMathConfig.h)

add_library(Math SHARED
            source/gsMath.cpp
            source/gsVector3.cpp
           )

add_library(OpenGS::Math ALIAS Math)

target_include_directories(Math PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/include
                           ${CMAKE_CURRENT_BINARY_DIR}/include
                          )

target_compile_definitions(Math PRIVATE BUILDING_MATH_SHARED)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/gsMathConfig.h DESTINATION include)