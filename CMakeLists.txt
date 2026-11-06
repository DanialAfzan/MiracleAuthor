cmake_minimum_required(VERSION 3.20)
project(MiracleAuthor LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional alternative for advanced users: CMake build.
# Normal Windows route is MiracleAuthor.sln + SETUP_SDL3.cmd.
set(SDL3_SDK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL3" CACHE PATH "SDL3 VC SDK folder")
if(WIN32 AND EXISTS "${SDL3_SDK_ROOT}/include/SDL3/SDL.h"
         AND EXISTS "${SDL3_SDK_ROOT}/lib/x64/SDL3.lib")
    add_library(SDL3_imported SHARED IMPORTED GLOBAL)
    set_target_properties(SDL3_imported PROPERTIES
        IMPORTED_IMPLIB "${SDL3_SDK_ROOT}/lib/x64/SDL3.lib"
        IMPORTED_LOCATION "${SDL3_SDK_ROOT}/lib/x64/SDL3.dll"
        INTERFACE_INCLUDE_DIRECTORIES "${SDL3_SDK_ROOT}/include")
    add_library(SDL3::SDL3 ALIAS SDL3_imported)
else()
    find_package(SDL3 CONFIG QUIET)
    if(NOT SDL3_FOUND)
        message(FATAL_ERROR "SDL3 not found. On Windows, run SETUP_SDL3.cmd with an extracted SDL3-devel-VC SDK, then reconfigure. If SDL3 is installed elsewhere, provide -DCMAKE_PREFIX_PATH=path/to/SDL3.")
    endif()
endif()

add_executable(MiracleAuthor
    src/main.cpp src/Game.cpp src/Level.cpp src/Player.cpp src/Enemy.cpp)
target_link_libraries(MiracleAuthor PRIVATE SDL3::SDL3)
add_custom_command(TARGET MiracleAuthor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
       "${CMAKE_CURRENT_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:MiracleAuthor>/assets")
if(WIN32 AND EXISTS "${SDL3_SDK_ROOT}/lib/x64/SDL3.dll")
    add_custom_command(TARGET MiracleAuthor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
         "${SDL3_SDK_ROOT}/lib/x64/SDL3.dll" "$<TARGET_FILE_DIR:MiracleAuthor>")
endif()
