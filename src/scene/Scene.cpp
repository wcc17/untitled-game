#include "../../includes/scene/Scene.h"

Logger Scene::logger("Scene");

std::string Scene::getSceneName() {
    return this->sceneName;
}