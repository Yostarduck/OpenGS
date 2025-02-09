cmake_minimum_required(VERSION 3.16)

project(OpenGS VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detect the architecture (Windows/MSVC: CMAKE_GENERATOR_PLATFORM, Other: CMAKE_SYSTEM_PROCESSOR)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_DIR "x64")
else()
    set(ARCH_DIR "x86")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ARCH_DIR}/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ARCH_DIR}/$<CONFIG>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${ARCH_DIR}/$<CONFIG>)

# Apply the same settings for all targets
foreach(OUTPUTCONFIG Debug Release RelWithDebInfo MinSizeRel)
    foreach(OUTPUTTYPE RUNTIME LIBRARY ARCHIVE)
        set(CMAKE_${OUTPUTTYPE}_OUTPUT_DIRECTORY_${OUTPUTCONFIG} 
            ${CMAKE_BINARY_DIR}/${ARCH_DIR}/${OUTPUTCONFIG})
    endforeach()
endforeach()

add_subdirectory(SDL)
add_subdirectory(FMath)
add_subdirectory(App)