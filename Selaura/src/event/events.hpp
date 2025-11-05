#pragma once
#include "event_manager.hpp"

#include <api/mc/client/gui/ScreenView.hpp>
#include <api/mc/client/renderer/MinecraftUIRenderContext.hpp>

namespace selaura {
    template <event_phase Phase>
    struct SetupAndRenderEvent : cancelable_event {
        ScreenView* mScreenView;
        MinecraftUIRenderContext* mCtx;
    };
};