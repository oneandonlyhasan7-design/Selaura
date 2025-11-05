#include "hooks.hpp"
#include <shadowhook.h>
#include <print>

#include "../runtime.hpp"
#include "memory.hpp"

#include <api/mc/world/Minecraft.hpp>
#include <api/mc/client/ClientInstance.hpp>
#include <api/mc/client/gui/ScreenView.hpp>

#include <event/events.hpp>

#include "spdlog/sinks/basic_file_sink-inl.h"

void* Minecraft_$ctor_original = nullptr;
void* ClientInstance_$ctor_original = nullptr;
void* ScreenView_setupAndRender_original = nullptr;

Minecraft *Minecraft::$ctor(void *app, void *gameCallbacks, void *allowList, void *permissionsFile,
                            void *filePathManager, void *maxPlayerIdleTime, void *eventing, void *network,
                            void *packetSender, void *clientSubId, void *simTimer, void *realTimer,
                            void *contentTierManager, void *serverMetrics) {
    auto original = reinterpret_cast<Minecraft*(*)(Minecraft*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*)>(Minecraft_$ctor_original);
    auto rt = original(this, app, gameCallbacks, allowList, permissionsFile, filePathManager, maxPlayerIdleTime, eventing, network, packetSender, clientSubId, simTimer, realTimer, contentTierManager, serverMetrics);

    if (selaura::runtime_instance->client_ctx->mMinecraft == nullptr) {
        selaura::runtime_instance->client_ctx->mMinecraft = rt;
        selaura::runtime_instance->mc_client_thread = std::this_thread::get_id();
    } else {
        selaura::runtime_instance->server_ctx->mMinecraft = rt;
        selaura::runtime_instance->mc_server_thread = std::this_thread::get_id();
    }
    return rt;
};

void *ClientInstance::$ctor(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8, void *a9) {
    auto original = reinterpret_cast<void*(*)(ClientInstance*, void*, void*, void*, void*, void*, void*, void*, void*, void*)>(ClientInstance_$ctor_original);
    auto rt = original(this, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    selaura::runtime_instance->client_ctx->mClientInstance = this;
    return rt;
}

void ScreenView::setupAndRender_hk(MinecraftUIRenderContext *ctx) {
    selaura::SetupAndRenderEvent<selaura::event_phase::pre> before_ev{};
    before_ev.mScreenView = this;
    before_ev.mCtx = ctx;

    selaura::runtime_instance->event_manager->post(before_ev);

    auto original = reinterpret_cast<void(*)(ScreenView*, MinecraftUIRenderContext*)>(ScreenView_setupAndRender_original);
    original(this, ctx);

    selaura::SetupAndRenderEvent<selaura::event_phase::post> after_ev{};
    after_ev.mScreenView = this;
    after_ev.mCtx = ctx;

    selaura::runtime_instance->event_manager->post(after_ev);
}

void selaura::init_hooks() {
    void* minecraft_addr = find_signature<"48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4D 8B E9 49 8B D8 4C 8B F2">();
    Minecraft_$ctor_original = shadowhook_hook_func_addr(minecraft_addr, reinterpret_cast<void*>(&Minecraft::$ctor), nullptr);

    void* screenview_addr = find_signature<"48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 BC 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA">();
    ScreenView_setupAndRender_original = shadowhook_hook_func_addr(screenview_addr, reinterpret_cast<void*>(&ScreenView::setupAndRender_hk), nullptr);
}
