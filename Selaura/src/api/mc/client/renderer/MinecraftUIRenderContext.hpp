#pragma once
#include <cstdint>
#include <glm/glm.hpp>
#include <gsl/gsl>

#include <api/mc/client/ClientInstance.hpp>

#pragma pack(push, 4)
struct RectangleArea {
    float _x0;
    float _x1;
    float _y0;
    float _y1;
};
#pragma pack(pop)

namespace mce {
    class Color {
    public:
        float r;
        float g;
        float b;
        float a;

        Color(float r, float g, float b, float a)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }

        Color(unsigned int color)
        {
            this->r = (float)((color & 0xFF000000) >> 24) / 255.0f;
            this->g = (float)((color & 0x00FF0000) >> 16) / 255.0f;
            this->b = (float)((color & 0x0000FF00) >> 8) / 255.0f;
            this->a = (float)((color & 0x000000FF)) / 255.0f;
        }

        Color()
        {
            this->r = 0.0f;
            this->g = 0.0f;
            this->b = 0.0f;
            this->a = 0.0f;
        }

        uint32_t As32() const
        {
            struct PackedColors {
                union {
                    struct {
                        char r;
                        char g;
                        char b;
                        char a;
                    };
                    unsigned int intValue;
                };
            };

            PackedColors result{};
            result.r = static_cast<char>(this->r * 255.0f);
            result.g = static_cast<char>(this->g * 255.0f);
            result.b = static_cast<char>(this->b * 255.0f);
            result.a = static_cast<char>(this->a * 255.0f);

            return result.intValue;
        }
    };

    class TexturePtr;
};

class Font;
class NinesliceInfo;
class HashedString;
class ComponentRenderBatch;
class CustomRenderComponent;
class ResourceLocation;

namespace Core {
    class Path;
};

class TextMeasureData;
class CaretMeasureData;

namespace ui {
    class TextAlignment;
};

class ScreenContext;

class MinecraftUIRenderContext {
public:
    ClientInstance* mClientInstance;
    ScreenContext* mScreenContext;
public:
    MinecraftUIRenderContext(ClientInstance& client, void* screenContext, void* currentScene);
    virtual ~MinecraftUIRenderContext();
    virtual float getLineLength(Font& font, const std::string& text, float fontSize, bool showColorSymbol);
    virtual float getTextAlpha();
    virtual void setTextAlpha(float alpha);
    virtual void drawDebugText(const RectangleArea& rect, const std::string& text, const mce::Color& color, float alpha, ui::TextAlignment alignment, const TextMeasureData& textData, const CaretMeasureData& caretData);
    virtual void drawText(Font& font, const RectangleArea& rect, const std::string& text, const mce::Color& color, float alpha, ui::TextAlignment alignment, const TextMeasureData& textData, const CaretMeasureData& caretData);
    virtual void flushText(float deltaTime);
    virtual void drawImage(const mce::TexturePtr& texture, const glm::tvec2<float>& position, const glm::tvec2<float>& size, glm::tvec2<float>& uv, glm::tvec2<float>& uvSize, int degree);
    virtual void drawNineslice(const mce::TexturePtr& texture, const NinesliceInfo& nineslice);
    virtual void flushImages(const mce::Color& color, float alpha, const HashedString& materialNameHash);
    virtual void beginSharedMeshBatch(ComponentRenderBatch& renderBatch);
    virtual void endSharedMeshBatch(ComponentRenderBatch& renderBatch);
    virtual void reserveSharedMeshBatch(uint64_t);
    virtual uint64_t getSharedMeshBatchVertexCount();
    virtual void drawRectangle(const RectangleArea& rect, const mce::Color& color, float alpha, int thickness);
    virtual void fillRectangle(const RectangleArea& rect, const mce::Color& color, float alpha);
    virtual void increaseStencilRef();
    virtual void decreaseStencilRef();
    virtual void resetStencilRef();
    virtual void fillRectangleStencil(const RectangleArea& rect);
    virtual void enableScissorTest(const RectangleArea& rect);
    virtual void disableScissorTest();
    virtual void setClippingRectangle(const RectangleArea& rect);
    virtual void setFullClippingRectangle();
    virtual void saveCurrentClippingRectangle();
    virtual void restoreSavedClippingRectangle();
    virtual RectangleArea getFullClippingRectangle();
    virtual bool updateCustom(gsl::not_null<CustomRenderComponent*> customRenderer);
    virtual void renderCustom(gsl::not_null<CustomRenderComponent*> customRenderer, int pass, RectangleArea& renderAABB);
    virtual void cleanup();
    virtual void removePersistentMeshes();
    virtual mce::TexturePtr getTexture(const ResourceLocation& resourceLocation, bool forceReload);
    virtual mce::TexturePtr getZippedTexture(const Core::Path& zippedFolderPath, const ResourceLocation& resourceLocation, bool forceReload);
    virtual void unloadTexture(ResourceLocation const &);
};