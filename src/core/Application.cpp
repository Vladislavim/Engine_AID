#include "core/Application.h"

#include "core/Logger.h"
#include "core/States.h"
#include "render/IRenderAdapter.h"

#include <iomanip>
#include <sstream>
#include <stdexcept>

Application::Application(std::unique_ptr<IRenderAdapter> renderer)
    : renderer_(std::move(renderer)) {}

Application::~Application() {
    shutdown();
}

bool Application::initialize() {
    if (initialized_) {
        return true;
    }

    Logger::instance().initialize("logs/app.log");
    Logger::instance().info("Application initialize");

    if (!renderer_ || !renderer_->initialize(1280, 720, "HW1 Engine Skeleton")) {
        Logger::instance().error("Render adapter initialization failed");
        return false;
    }

    scene_.primitive.size = {120.0f, 120.0f};
    scene_.primitive.scale = 1.0f;
    scene_.primitive.rotationDeg = 0.0f;
    scene_.primitive.position = {640.0f, 360.0f};

    changeState(GameStateType::Loading);
    lastFrameTime_ = std::chrono::steady_clock::now();
    initialized_ = true;
    return true;
}

void Application::run() {
    if (!initialized_ && !initialize()) {
        return;
    }

    running_ = true;
    Logger::instance().info("Main loop started");

    while (running_ && !renderer_->windowShouldClose()) {
        const auto now = std::chrono::steady_clock::now();
        const std::chrono::duration<double> dtDuration = now - lastFrameTime_;
        lastFrameTime_ = now;

        double dt = dtDuration.count();
        if (dt > 0.25) {
            dt = 0.25;
        }

        dtLogTimer_ += dt;
        if (dtLogTimer_ >= 0.5) {
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(4) << "deltaTime=" << dt;
            Logger::instance().info(ss.str());
            dtLogTimer_ = 0.0;
        }

        const InputFrame input = renderer_->pollInput();
        scene_.windowSize = renderer_->getWindowSize();
        handleGlobalStateSwitch(input);

        if (state_) {
            if (auto next = state_->update(dt, input, scene_); next.has_value()) {
                changeState(*next);
            }
        }

        renderer_->beginFrame(clearColorForState());
        if (state_) {
            state_->render(*renderer_, scene_);
        }
        renderer_->endFrame();
    }

    Logger::instance().info("Main loop finished");
}

void Application::shutdown() {
    if (!initialized_) {
        return;
    }

    if (state_) {
        Logger::instance().info(std::string("Exit state: ") + state_->name());
        state_->onExit();
        state_.reset();
    }

    if (renderer_) {
        renderer_->shutdown();
    }

    Logger::instance().info("Application shutdown");
    Logger::instance().shutdown();
    initialized_ = false;
    running_ = false;
}

void Application::changeState(GameStateType nextState) {
    if (state_) {
        Logger::instance().info(std::string("Exit state: ") + state_->name());
        state_->onExit();
    }

    state_ = createState(nextState);
    if (!state_) {
        throw std::runtime_error("State creation failed");
    }

    Logger::instance().info(std::string("Enter state: ") + state_->name());
    state_->onEnter();
}

std::unique_ptr<GameState> Application::createState(GameStateType type) const {
    switch (type) {
    case GameStateType::Loading:
        return std::make_unique<LoadingState>();
    case GameStateType::Menu:
        return std::make_unique<MenuState>();
    case GameStateType::Gameplay:
        return std::make_unique<GameplayState>();
    }
    return {};
}

void Application::handleGlobalStateSwitch(const InputFrame& input) {
    if (input.key1) {
        changeState(GameStateType::Loading);
    } else if (input.key2) {
        changeState(GameStateType::Menu);
    } else if (input.key3) {
        changeState(GameStateType::Gameplay);
    }
}

ColorRGBA Application::clearColorForState() const {
    if (!state_) {
        return {20, 20, 20, 255};
    }

    const std::string name = state_->name();
    if (name == "Loading") {
        return {26, 32, 48, 255};
    }
    if (name == "Menu") {
        return {38, 49, 46, 255};
    }
    return {18, 18, 28, 255};
}
