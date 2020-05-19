#include "../../includes/scene/PlayerManager.h"

void PlayerManager::initialize(
        std::shared_ptr<EventBus> eventBus,
        TextureManager& textureManager) {
    textureManager.loadTexture(AssetPath::PLAYER_TEXTURE);

    playerEntity = std::make_shared<PlayerEntity>();
    playerEntity->initialize(eventBus, textureManager.getTexture(AssetPath::PLAYER_TEXTURE));
}

std::shared_ptr<PlayerEntity> PlayerManager::getPlayerEntity() {
    return this->playerEntity;
}

void PlayerManager::release(TextureManager& textureManager) {
    playerEntity->release();
    textureManager.releaseTexture(AssetPath::PLAYER_TEXTURE);
}
