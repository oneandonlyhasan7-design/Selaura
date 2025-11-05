#pragma once
#include <optional>
#include <thread>

#include "context.hpp"
#include <event/event_manager.hpp>

namespace selaura {
    struct runtime {
        std::thread::id thread_id;
        std::optional<std::thread::id> mc_client_thread;
        std::optional<std::thread::id> mc_server_thread;

        std::unique_ptr<client_context> client_ctx;
        std::unique_ptr<server_context> server_ctx;

        std::unique_ptr<event_manager> event_manager;

        runtime(const runtime_context& ctx);
        void start();

        bool unload = false;
        bool ready = false;
    };

    inline std::shared_ptr<runtime> runtime_instance;
};