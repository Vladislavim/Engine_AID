#include "core/Application.h"
#include "render/RaylibRenderAdapter.h"

#include <exception>
#include <iostream>
#include <memory>

int main() {
    try {
        auto renderer = std::make_unique<RaylibRenderAdapter>();
        Application app(std::move(renderer));
        if (!app.initialize()) {
            return 1;
        }
        app.run();
        app.shutdown();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
