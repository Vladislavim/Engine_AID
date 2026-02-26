#pragma once

#include "core/GameState.h"

#include <chrono>
#include <memory>

class IRenderAdapter;

class Application {
public:
    explicit Application(std::unique_ptr<IRenderAdapter> renderer);
    ~Application();

    bool initialize();
    void run();
    void shutdown();

private:
    void changeState(GameStateType nextState);
    std::unique_ptr<GameState> createState(GameStateType type) const;
    void handleGlobalStateSwitch(const InputFrame& input);
    ColorRGBA clearColorForState() const;

    std::unique_ptr<IRenderAdapter> renderer_;
    std::unique_ptr<GameState> state_;
    SharedSceneData scene_;
    bool initialized_{false};
    bool running_{false};
    std::chrono::steady_clock::time_point lastFrameTime_{};
    double dtLogTimer_{0.0};
};
