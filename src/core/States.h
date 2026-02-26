#pragma once

#include "core/GameState.h"
#include "game/InputController.h"

#include <optional>

class LoadingState final : public GameState {
public:
    const char* name() const override;
    void onEnter() override;
    std::optional<GameStateType> update(double dt, const InputFrame& input, SharedSceneData& scene) override;
    void render(IRenderAdapter& renderer, SharedSceneData& scene) override;

private:
    double timer_{0.0};
};

class MenuState final : public GameState {
public:
    const char* name() const override;
    std::optional<GameStateType> update(double dt, const InputFrame& input, SharedSceneData& scene) override;
    void render(IRenderAdapter& renderer, SharedSceneData& scene) override;
};

class GameplayState final : public GameState {
public:
    const char* name() const override;
    std::optional<GameStateType> update(double dt, const InputFrame& input, SharedSceneData& scene) override;
    void render(IRenderAdapter& renderer, SharedSceneData& scene) override;

private:
    void ensureCenter(SharedSceneData& scene, const WindowSize& size);

    InputController inputController_;
    bool initialized_{false};
};
