#ifndef NEWNEW_COLLIDABLEENTITY_H
#define NEWNEW_COLLIDABLEENTITY_H


#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include "../../collisions/Collidable.h"

class CollidableEntity : public Collidable, public virtual sf::Sprite {
public:
    void fixPositionAfterCollision(const Collidable& collidedWith, MoveDirection entityDirection);
    sf::FloatRect getBoundingBox() const override;
    sf::FloatRect getVicinityBounds() const;
    void addCollidableInVicinity(std::shared_ptr<Collidable> collidable);
    void clearCollidablesInVicinity();
    bool isFacingCollidableInVicinity(MoveDirection facingDirection, Collidable& collidableInVicinity);

protected:
    void setVicinityBoundsOffset(int vicinityBoundsOffset);
    std::vector<std::shared_ptr<Collidable>> collidablesInVicinity;

private:
    static bool isEntityRectAlignedWithCollidableRect(MoveDirection facingDirection,
            sf::FloatRect& entityRect, sf::FloatRect& collidableRect);
    int vicinityBoundsOffset;
};


#endif //NEWNEW_COLLIDABLEENTITY_H
