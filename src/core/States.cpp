#include "core/States.h"

#include <algorithm>

const char* LoadingState::name() const {
    return "Loading";
}

void LoadingState::onEnter() {
    timer_ = 0.0;
}

std::optional<GameStateType> LoadingState::update(double dt, const InputFrame&, SharedSceneData&) {
    timer_ += dt;
    if (timer_ >= 1.2) {
        return GameStateType::Menu;
    }
    return std::nullopt;
}

void LoadingState::render(IRenderAdapter& renderer, SharedSceneData&) {
    renderer.drawTextLine("Loading...", 20, 20, 26, {235, 235, 235, 255});
    renderer.drawTextLine("State system ready", 20, 60, 20, {190, 190, 190, 255});
}

const char* MenuState::name() const {
    return "Menu";
}

std::optional<GameStateType> MenuState::update(double, const InputFrame& input, SharedSceneData&) {
    if (input.enter) {
        return GameStateType::Gameplay;
    }
    return std::nullopt;
}

void MenuState::render(IRenderAdapter& renderer, SharedSceneData&) {
    renderer.drawTextLine("Menu state", 20, 20, 26, {255, 255, 255, 255});
    renderer.drawTextLine("Enter - start gameplay", 20, 60, 20, {210, 210, 210, 255});
    renderer.drawTextLine("1/2/3 - switch states", 20, 88, 20, {210, 210, 210, 255});
}

const char* GameplayState::name() const {
    return "Gameplay";
}

void GameplayState::ensureCenter(SharedSceneData& scene, const WindowSize& size) {
    if (initialized_) {
        return;
    }
    if (scene.primitive.position.x == 0.0f && scene.primitive.position.y == 0.0f) {
        scene.primitive.position.x = size.width * 0.5f;
        scene.primitive.position.y = size.height * 0.5f;
    }
    scene.primitive.size = {120.0f, 120.0f};
    scene.primitive.scale = std::clamp(scene.primitive.scale, 0.2f, 4.0f);
    initialized_ = true;
}

std::optional<GameStateType> GameplayState::update(double dt, const InputFrame& input, SharedSceneData& scene) {
    if (input.escape) {
        return GameStateType::Menu;
    }
    ensureCenter(scene, scene.windowSize);
    inputController_.updateFromInput(input, dt, scene.primitive, scene.windowSize);
    return std::nullopt;
}

void GameplayState::render(IRenderAdapter& renderer, SharedSceneData& scene) {
    renderer.drawPrimitive(scene.primitive, {53, 180, 255, 255});
    renderer.drawTextLine("Gameplay state", 20, 20, 26, {255, 255, 255, 255});
    renderer.drawTextLine("Arrows - move", 20, 60, 20, {210, 210, 210, 255});
    renderer.drawTextLine("LMB - scale, RMB - rotate, Esc - menu", 20, 88, 20, {210, 210, 210, 255});
}
