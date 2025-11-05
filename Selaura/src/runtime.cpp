#include "runtime.hpp"

#include <print>

#include "hooks/hooks.hpp"

namespace selaura {
    runtime::runtime(const runtime_context& ctx) {
        std::println("[Selaura Runtime] Created runtime.");
        std::println("[Selaura Runtime] Running on Minecraft Version: {}.{}.{}.{}",
            ctx.version_major,
            ctx.version_minor,
            ctx.version_build,
            ctx.version_revision);

        this->thread_id = ctx.thread_id;

        this->client_ctx = std::make_unique<client_context>();
        this->server_ctx = std::make_unique<server_context>();
        this->event_manager = std::make_unique<selaura::event_manager>();
    }

    void runtime::start(){
        selaura::init_hooks();
    }
};