#ifndef NEWNEW_BATTLESCENE_H
#define NEWNEW_BATTLESCENE_H


#include "Scene.h"
#include "../npc/NpcManager.h"
#include "../collisions/CollisionManager.h"
#include "ViewManager.h"

class BattleScene : public Scene {

public:
    virtual void initialize(
            std::shared_ptr<EventBus> eventBus,
            std::string sceneName,
            std::string previousSceneName,
            TextureManager& textureManager) override;
    virtual void update(sf::Time elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void release(TextureManager& textureManager) override;

private:
    std::shared_ptr<EventBus> eventBus;
};


#endif //NEWNEW_BATTLESCENE_H
