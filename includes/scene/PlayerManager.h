#ifndef NEWNEW_PLAYERMANAGER_H
#define NEWNEW_PLAYERMANAGER_H


#include "../entity/player/PlayerEntity.h"
#include "../asset/AssetPath.h"
#include "../asset/TextureManager.h"

class PlayerManager {

public:
    void initialize(
            std::shared_ptr<EventBus> eventBus,
            TextureManager& textureManager);
    std::shared_ptr<PlayerEntity> getPlayerEntity();
    void release(TextureManager& textureManager);
private:
    std::shared_ptr<PlayerEntity> playerEntity;
};


#endif //NEWNEW_PLAYERMANAGER_H
