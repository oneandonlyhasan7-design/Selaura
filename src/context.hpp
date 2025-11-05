#pragma once
#include <thread>

#include <api/mc/world/Minecraft.hpp>
#include <api/mc/client/ClientInstance.hpp>

namespace selaura {
    struct shared_context {
        Minecraft* mMinecraft;
    };

    struct client_context : shared_context {
        ClientInstance* mClientInstance;
    };

    struct server_context : shared_context {};

    struct runtime_context {
        std::thread::id thread_id;
        int version_major;
        int version_minor;
        int version_build;
        int version_revision;

        client_context* client_ctx;
        server_context* server_ctx;
    };
};