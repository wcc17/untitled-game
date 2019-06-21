#ifndef NEWNEW_NPCENTITY_H
#define NEWNEW_NPCENTITY_H


#include "CharacterEntity.h"

class NpcEntity : public CharacterEntity {

public:
    void initialize(sf::Texture* texture, const Collidable& collidable);
    void update(sf::Time deltaTime);
protected:
    void initializeAnimations() override;
};


#endif //NEWNEW_NPCENTITY_H
