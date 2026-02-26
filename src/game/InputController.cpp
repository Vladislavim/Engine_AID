#include "game/InputController.h"

#include <algorithm>

void InputController::scaleAroundCenter(PrimitiveTransform& transform, WindowSize windowSize, float factor) {
    const float cx = windowSize.width * 0.5f;
    const float cy = windowSize.height * 0.5f;
    transform.position.x = cx + (transform.position.x - cx) * factor;
    transform.position.y = cy + (transform.position.y - cy) * factor;
}

void InputController::handleMouseActions(const InputFrame& input) {
    if (input.mouseLeftPressed) {
        targetScale_ += 0.2f;
        if (targetScale_ > 2.4f) {
            targetScale_ = 0.6f;
        }
    }
    if (input.mouseRightPressed) {
        targetRotation_ += 30.0f;
        if (targetRotation_ > 3600.0f) {
            targetRotation_ -= 3600.0f;
        }
    }
}

void InputController::updateFromInput(const InputFrame& input, double dt, PrimitiveTransform& transform, WindowSize windowSize) {
    if (input.mouseLeftPressed) {
        scaleAroundCenter(transform, windowSize, 1.08f);
    }
    handleMouseActions(input);

    const float moveSpeed = 240.0f;
    const float moveStep = static_cast<float>(dt) * moveSpeed;

    if (input.up) {
        transform.position.y -= moveStep;
    }
    if (input.down) {
        transform.position.y += moveStep;
    }
    if (input.left) {
        transform.position.x -= moveStep;
    }
    if (input.right) {
        transform.position.x += moveStep;
    }

    const float sLerp = std::min(1.0f, static_cast<float>(dt) * 8.0f);
    const float rLerp = std::min(1.0f, static_cast<float>(dt) * 10.0f);

    transform.scale += (targetScale_ - transform.scale) * sLerp;
    transform.rotationDeg += (targetRotation_ - transform.rotationDeg) * rLerp;
    transform.scale = std::clamp(transform.scale, 0.2f, 4.0f);

    const float halfW = transform.size.x * transform.scale * 0.5f;
    const float halfH = transform.size.y * transform.scale * 0.5f;
    transform.position.x = std::clamp(transform.position.x, halfW, static_cast<float>(windowSize.width) - halfW);
    transform.position.y = std::clamp(transform.position.y, halfH, static_cast<float>(windowSize.height) - halfH);
}
