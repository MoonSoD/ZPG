#pragma once

#include "Light.h"

class SpotLight : public Light {
public:
    SpotLight(const glm::vec3& position, const glm::vec3& direction, float cutoffAngle) 
     : Light(3, position, direction, cutoffAngle) {
    }
};