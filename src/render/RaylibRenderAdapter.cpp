#include "render/RaylibRenderAdapter.h"

#include "raylib.h"

namespace {
Color ToRayColor(const ColorRGBA& c) {
    return Color{c.r, c.g, c.b, c.a};
}
}

bool RaylibRenderAdapter::initialize(int width, int height, const std::string& title) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(width, height, title.c_str());
    if (!IsWindowReady()) {
        return false;
    }
    SetTargetFPS(144);
    initialized_ = true;
    return true;
}

bool RaylibRenderAdapter::windowShouldClose() const {
    return initialized_ ? WindowShouldClose() : true;
}

InputFrame RaylibRenderAdapter::pollInput() {
    InputFrame input{};
    input.up = IsKeyDown(KEY_UP);
    input.down = IsKeyDown(KEY_DOWN);
    input.left = IsKeyDown(KEY_LEFT);
    input.right = IsKeyDown(KEY_RIGHT);
    input.enter = IsKeyPressed(KEY_ENTER);
    input.escape = IsKeyPressed(KEY_ESCAPE);
    input.key1 = IsKeyPressed(KEY_ONE);
    input.key2 = IsKeyPressed(KEY_TWO);
    input.key3 = IsKeyPressed(KEY_THREE);
    input.mouseLeftPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    input.mouseRightPressed = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    return input;
}

WindowSize RaylibRenderAdapter::getWindowSize() const {
    return WindowSize{GetScreenWidth(), GetScreenHeight()};
}

void RaylibRenderAdapter::beginFrame(const ColorRGBA& clearColor) {
    BeginDrawing();
    ClearBackground(ToRayColor(clearColor));
}

void RaylibRenderAdapter::drawPrimitive(const PrimitiveTransform& transform, const ColorRGBA& color) {
    const float width = transform.size.x * transform.scale;
    const float height = transform.size.y * transform.scale;
    Rectangle rect{
        transform.position.x - width * 0.5f,
        transform.position.y - height * 0.5f,
        width,
        height
    };
    Vector2 origin{width * 0.5f, height * 0.5f};
    DrawRectanglePro(rect, origin, transform.rotationDeg, ToRayColor(color));
}

void RaylibRenderAdapter::drawTextLine(const std::string& text, int x, int y, int fontSize, const ColorRGBA& color) {
    DrawText(text.c_str(), x, y, fontSize, ToRayColor(color));
}

void RaylibRenderAdapter::endFrame() {
    EndDrawing();
}

void RaylibRenderAdapter::shutdown() {
    if (initialized_) {
        CloseWindow();
        initialized_ = false;
    }
}
