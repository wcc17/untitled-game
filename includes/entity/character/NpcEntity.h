#ifndef NEWNEW_NPCENTITY_H
#define NEWNEW_NPCENTITY_H


#include "CharacterEntity.h"

class NpcEntity : public CharacterEntity {

public:
    void initialize(sf::Texture* texture, const Collidable& collidable);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) override;
    void turnToFacePlayer(MoveDirection playerFacingDirection);
private:
    void initializeAnimations() override;
    void handleStandingState(sf::Time deltaTime) override;
    void handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) override;
    void handleInteractingState() override;
};


#endif //NEWNEW_NPCENTITY_H
