cmake_minimum_required(VERSION 3.16)

set(GRAPHICS_VERSION_MAJOR 1)
set(GRAPHICS_VERSION_MINOR 0)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gsGraphicsConfig.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/gsGraphicsConfig.h)

add_library(Graphics SHARED
            source/gsVertex.cpp
            source/gsTriangle.cpp
            source/gsColor.cpp)

add_library(OpenGS::Graphics ALIAS Graphics)

target_link_libraries(Graphics PRIVATE
                      OpenGS::Math)

target_include_directories(Graphics PRIVATE
                           ${CMAKE_SOURCE_DIR}/Math/include)

target_include_directories(Graphics PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/include
                           ${CMAKE_CURRENT_BINARY_DIR}/include
                          )

target_compile_definitions(Graphics PRIVATE BUILDING_GRAPHICS_SHARED)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/gsGraphicsConfig.h DESTINATION include)