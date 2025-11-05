#pragma once

#include <api/mc/client/renderer/MinecraftUIRenderContext.hpp>

class ScreenView {
public:
    void setupAndRender(MinecraftUIRenderContext&);
public:
    void setupAndRender_hk(MinecraftUIRenderContext* ctx);
};
