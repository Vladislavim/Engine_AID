#pragma once

#include "render/IRenderAdapter.h"

class RaylibRenderAdapter final : public IRenderAdapter {
public:
    bool initialize(int width, int height, const std::string& title) override;
    bool windowShouldClose() const override;
    InputFrame pollInput() override;
    WindowSize getWindowSize() const override;

    void beginFrame(const ColorRGBA& clearColor) override;
    void drawPrimitive(const PrimitiveTransform& transform, const ColorRGBA& color) override;
    void drawTextLine(const std::string& text, int x, int y, int fontSize, const ColorRGBA& color) override;
    void endFrame() override;
    void shutdown() override;

private:
    bool initialized_{false};
};
