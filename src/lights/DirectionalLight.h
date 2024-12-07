#pragma once

#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(const glm::vec3& direction
    ) : Light(2, glm::vec3(0, 0, 0), direction) {
    }
};