#ifndef NEWNEW_ENTITYCOLLIDABLE_H
#define NEWNEW_ENTITYCOLLIDABLE_H


#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include "../../collisions/Collidable.h"
#include "../../util/Logger.h"
#include "EntityLogger.h"

class EntityCollidable : public Collidable {
public:
    void initialize(const Collidable& collidable);
    sf::FloatRect getVicinityBounds() const;
    std::vector<std::shared_ptr<Collidable>> getCollidablesInVicinity();
    void setVicinityBoundsOffset(int vicinityBoundsOffset);
    void addCollidableInVicinity(std::shared_ptr<Collidable> collidable);
    void clearCollidablesInVicinity();
    bool isFacingCollidableInVicinity(MoveDirection facingDirection, Collidable& collidableInVicinity);

protected:
    std::vector<std::shared_ptr<Collidable>> collidablesInVicinity;

private:
    int vicinityBoundsOffset;
    EntityLogger entityLogger;
};


#endif //NEWNEW_ENTITYCOLLIDABLE_H
