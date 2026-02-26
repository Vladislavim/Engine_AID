#pragma once

#include <string>

struct Vec2 {
    float x{};
    float y{};
};

struct ColorRGBA {
    unsigned char r{};
    unsigned char g{};
    unsigned char b{};
    unsigned char a{255};
};

struct PrimitiveTransform {
    Vec2 position{};
    Vec2 size{120.0f, 120.0f};
    float rotationDeg{};
    float scale{1.0f};
};

struct InputFrame {
    bool up{};
    bool down{};
    bool left{};
    bool right{};
    bool enter{};
    bool escape{};
    bool key1{};
    bool key2{};
    bool key3{};
    bool mouseLeftPressed{};
    bool mouseRightPressed{};
};

struct WindowSize {
    int width{};
    int height{};
};

class IRenderAdapter {
public:
    virtual ~IRenderAdapter() = default;

    virtual bool initialize(int width, int height, const std::string& title) = 0;
    virtual bool windowShouldClose() const = 0;
    virtual InputFrame pollInput() = 0;
    virtual WindowSize getWindowSize() const = 0;

    virtual void beginFrame(const ColorRGBA& clearColor) = 0;
    virtual void drawPrimitive(const PrimitiveTransform& transform, const ColorRGBA& color) = 0;
    virtual void drawTextLine(const std::string& text, int x, int y, int fontSize, const ColorRGBA& color) = 0;
    virtual void endFrame() = 0;
    virtual void shutdown() = 0;
};
