#pragma once
#include <api/mc/client/renderer/MinecraftUIRenderContext.hpp>
#include <glm/glm.hpp>
#include <concepts>

namespace selaura {
    struct mcuirc {
        MinecraftUIRenderContext* ctx;
        explicit mcuirc(MinecraftUIRenderContext* _ctx) noexcept : ctx(_ctx) {}

        void draw_rect(float x, float y, float width, float height,
                       const glm::vec4& color,
                       bool stroke = false, int stroke_width = 1) const noexcept {
            const RectangleArea area{x, x + width, y, y + height};
            const mce::Color c{color.x, color.y, color.z, color.w};

            if (stroke) {
                ctx->drawRectangle(area, c, color.z, stroke_width);
            }
            else {
                ctx->fillRectangle(area, c, color.w);
            }
        }

        void draw_rect(const glm::vec2& pos, const glm::vec2& size,
                       const glm::vec4& color,
                       bool stroke = false, int stroke_width = 1) const noexcept {
            draw_rect(pos.x, pos.y, size.x, size.y, color, stroke, stroke_width);
        }

        void fill_rect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color) const noexcept {
            draw_rect(pos, size, color, false);
        }

        void stroke_rect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, int width = 1) const noexcept {
            draw_rect(pos, size, color, true, width);
        }

        void draw_rect(const glm::vec4& rect, const glm::vec4& color,
                       bool stroke = false, int stroke_width = 1) const noexcept {
            draw_rect(rect.x, rect.y, rect.z, rect.w, color, stroke, stroke_width);
        }
    };

}
