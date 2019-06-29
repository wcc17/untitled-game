#ifndef NEWNEW_NPCMANAGER_H
#define NEWNEW_NPCMANAGER_H

#include "../entity/character/NpcEntity.h"
#include "../../includes/asset/AssetPath.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "../events/EventBus.h"
#include "../events/event/StartEntityDialogueEvent.h"

class NpcManager {

public:
    void initialize(std::shared_ptr<EventBus> eventBus, std::vector<Collidable> collidables, sf::Texture* texture);
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow* window);
    std::vector<std::shared_ptr<NpcEntity>>& getNpcEntities();
    void release();
private:
    std::shared_ptr<EventBus> eventBus;
    std::vector<std::shared_ptr<NpcEntity>> npcs;
    void onStartEntityDialogueEvent(StartEntityDialogueEvent* event);
};


#endif //NEWNEW_NPCMANAGER_H
