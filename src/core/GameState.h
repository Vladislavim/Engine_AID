#pragma once

#include "render/IRenderAdapter.h"

#include <optional>
#include <string>

enum class GameStateType {
    Loading,
    Menu,
    Gameplay
};

struct SharedSceneData {
    PrimitiveTransform primitive{};
    WindowSize windowSize{1280, 720};
};

class GameState {
public:
    virtual ~GameState() = default;

    virtual const char* name() const = 0;
    virtual void onEnter() {}
    virtual void onExit() {}
    virtual std::optional<GameStateType> update(double dt, const InputFrame& input, SharedSceneData& scene) = 0;
    virtual void render(IRenderAdapter& renderer, SharedSceneData& scene) = 0;
};
