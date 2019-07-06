#ifndef NEWNEW_ENTITYCOLLIDABLE_H
#define NEWNEW_ENTITYCOLLIDABLE_H


#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include "../../collisions/Collidable.h"
#include "../../../includes/util/Logger.h"

class EntityCollidable : public Collidable {
public:
    void initialize(const Collidable& collidable);
    sf::Vector2f getFixedPositionAfterCollision(const Collidable& collidedWith, MoveDirection entityDirection);
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
    static void adjustPositionsByOne(MoveDirection entityDirection, int& left, int& top);
    static Logger logger;
};


#endif //NEWNEW_ENTITYCOLLIDABLE_H
