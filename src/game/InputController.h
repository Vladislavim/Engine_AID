#pragma once

#include "render/IRenderAdapter.h"

class InputController {
public:
    void updateFromInput(const InputFrame& input, double dt, PrimitiveTransform& transform, WindowSize windowSize);
    void handleMouseActions(const InputFrame& input);

private:
    void scaleAroundCenter(PrimitiveTransform& transform, WindowSize windowSize, float factor);

    float targetScale_{1.0f};
    float targetRotation_{0.0f};
};
