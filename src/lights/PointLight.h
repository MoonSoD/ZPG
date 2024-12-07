#pragma once

#include "Light.h"

class PointLight : public Light {
public:
    PointLight(const glm::vec3& position, const glm::vec3& direction
    ) : Light(1, position, direction) {
    }
};