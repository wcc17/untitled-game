#include "../../includes/scene/BattleScene.h"

void BattleScene::initialize(
        std::shared_ptr<EventBus> eventBus,
        std::string sceneName,
        std::string previousSceneName,
        TextureManager& textureManager) {
    this->sceneName = sceneName;
    this->eventBus = eventBus;
}

void BattleScene::update(sf::Time elapsedTime) {
//    eventBus->publish(new OpenDialogueEvent(getGlobalBounds(), *collidable, currentlyFacingDirection));
}

void BattleScene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//    states.transform *= getTransform();
//    states.texture = texture;
    target.clear(sf::Color::White);
}

void BattleScene::release(TextureManager& textureManager) {
}