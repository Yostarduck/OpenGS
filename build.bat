@echo off
setlocal enabledelayedexpansion

set BUILD_TYPE=Debug

if not "%1"=="" (
    set ARG=%1
    set ARG=!ARG:"=!
    if /I "%ARG%"=="Release" set BUILD_TYPE=Release
    if /I "%ARG%"=="Debug" set BUILD_TYPE=Debug
    else (
        echo Invalid Build Type: %ARG%
        echo Valid Build Types: Debug, Release
        echo Defaulting to Debug
    )
)

echo Selected Build Type: %BUILD_TYPE%

rm -rf Build

cmake -B Build -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
cmake --build Build --config %BUILD_TYPE%