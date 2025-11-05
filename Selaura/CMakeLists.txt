cmake_minimum_required(VERSION 3.28)
project(selaura LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

set(RUNTIME_VERSION "0.10")

if (ANDROID)
    add_compile_definitions(SELAURA_ANDROID)
    message(STATUS "Selaura: Building for Android (${ANDROID_ABI})")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall" CACHE STRING "" FORCE)
elseif (WIN32)
    add_compile_definitions(SELAURA_WINDOWS)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        if (CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
            message(STATUS "Selaura: Clang-cl detected (beware there may be issues using this, as it is not tested).")
        else()
            message(FATAL_ERROR "Selaura: Native Clang is not supported on Windows. Use MSVC or Clang-cl.")
        endif ()
    elseif (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        message(FATAL_ERROR "Selaura: Only MSVC or Clang-cl are supported on Windows.")
    endif ()

    add_compile_options(/await)
elseif (UNIX)
    add_compile_definitions(SELAURA_LINUX)
    if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(FATAL_ERROR "Selaura: Clang is required on Linux.")
    endif ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -fPIC" CACHE STRING "" FORCE)
else()
    message(FATAL_ERROR "Selaura: ${CMAKE_SYSTEM_NAME} (${CMAKE_SYSTEM_PROCESSOR}) is not supported")
endif ()

if (MSVC AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Od" CACHE STRING "" FORCE)

    add_compile_definitions(
            _ITERATOR_DEBUG_LEVEL=0
            _HAS_ITERATOR_DEBUGGING=0
            _SECURE_SCL=0
    )
endif()

add_compile_definitions(
        RUNTIME_VERSION=\"${RUNTIME_VERSION}\"
)

execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        RESULT_VARIABLE GIT_RESULT
)

if(NOT GIT_RESULT EQUAL 0)
    set(GIT_BRANCH "unknown")
endif()

add_compile_definitions(GIT_BRANCH="${GIT_BRANCH}")

add_subdirectory(include)
add_subdirectory(src)

if (WIN32)
    add_subdirectory(src-proxy)
    add_subdirectory(test)
endif()

if (MSVC)
    add_compile_options(/W4 /permissive- /wd4201 /wd4324)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-gnu-zero-variadic-macro-arguments)
endif ()