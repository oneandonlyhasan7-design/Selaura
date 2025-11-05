cmake_minimum_required(VERSION 3.28)
project(selaura_runtime LANGUAGES CXX)

set(SELAURA_SOURCES
        main.cpp
        runtime.cpp
        hooks/hooks.cpp
)

if(ANDROID)
    list(APPEND SELAURA_SOURCES android_jni.cpp)
endif()

add_library(selaura_runtime SHARED ${SELAURA_SOURCES})

target_compile_definitions(selaura_runtime PRIVATE SELAURA_RUNTIME_EXPORTS)

target_include_directories(selaura_runtime PRIVATE
        fmt
        EnTT
        spdlog
        libhat
        gsl
        glm
        safetyhook
        glaze
        magic_enum

        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(selaura_runtime PRIVATE
        EnTT::EnTT
        spdlog
        libhat
        Microsoft.GSL::GSL
        glm
        safetyhook::safetyhook
        glaze::glaze
        magic_enum::magic_enum
)

if (WIN32)
    target_link_libraries(selaura_runtime PRIVATE
            runtimeobject.lib
            version.lib
    )
elseif(ANDROID)
    target_link_libraries(selaura_runtime PRIVATE
            log
            android
    )
endif()
