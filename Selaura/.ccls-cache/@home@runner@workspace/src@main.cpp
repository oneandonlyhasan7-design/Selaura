#ifdef _WIN32
#include <Windows.h>

BOOL APIENTRY DllMain(HINSTANCE, DWORD, LPVOID) {
    return TRUE;
}
#endif

#include <api/imports.hpp>
#include <print>
#include "runtime.hpp"

SELAURA_API void SelauraRuntimeInit(selaura::runtime_context* ctx, std::function<void(selaura::runtime*)> load_mods) {
    selaura::runtime_instance = std::make_unique<selaura::runtime>(*ctx);
    selaura::runtime_instance->start();

    load_mods(selaura::runtime_instance.get());
}