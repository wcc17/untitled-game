#ifndef NEWNEW_NPCMANAGER_H
#define NEWNEW_NPCMANAGER_H

#include "../entity/character/NpcEntity.h"
#include "../../includes/asset/AssetPath.h"
#include "SFML/Graphics/RenderWindow.hpp"

class NpcManager {

public:
    void initialize(std::vector<Collidable> collidables, sf::Texture* texture);
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow* window);
    std::vector<std::shared_ptr<NpcEntity>>& getNpcEntities(); //NOTE: returning a reference since they are used so often. Take care not to modify
    void release();
private:
    std::vector<std::shared_ptr<NpcEntity>> npcs;
};


#endif //NEWNEW_NPCMANAGER_H
