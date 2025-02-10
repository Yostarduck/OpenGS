cmake_minimum_required(VERSION 3.16)

set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 0)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/AppConfig.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/AppConfig.h)

add_executable(App main.cpp)

target_link_libraries(App PRIVATE SDL3::SDL3 FMath)

target_include_directories(App PRIVATE
                           ${CMAKE_SOURCE_DIR}/SDL/include/SDL3
                           ${CMAKE_SOURCE_DIR}/FMath
                           ${CMAKE_CURRENT_BINARY_DIR}
                          )

target_compile_definitions(App PRIVATE APP_USES_SHARED_FMATH)