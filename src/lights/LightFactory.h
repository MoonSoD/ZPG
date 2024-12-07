#include "Light.h"

class LightFactory {
    static Light* createLight(int type, glm::vec3& position, glm::vec3& direction, glm::vec3& color);
}