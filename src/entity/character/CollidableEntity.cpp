#include "../../../includes/entity/character/CollidableEntity.h"

void CollidableEntity::fixPositionAfterCollision(const Collidable& collidedWith, MoveDirection entityDirection) {
    bool isColliding = true;
    float left = getBoundingBox().left;
    float top = getBoundingBox().top;
    while(isColliding) {
        if(entityDirection == MoveDirection::NONE) {
            printf("error with entity collision - the entity didn't move into this collision so theres no way to move him out\n");
        }

        if(entityDirection == MoveDirection::RIGHT) {
            left -= 1;
        } else if(entityDirection == MoveDirection::LEFT) {
            left += 1;
        }

        if(entityDirection == MoveDirection::DOWN) {
            top -= 1;
        } else if(entityDirection == MoveDirection::UP) {
            top += 1;
        }

        sf::FloatRect newBounds = sf::FloatRect(left, top, getBoundingBox().width, getBoundingBox().height);
        if(!newBounds.intersects(collidedWith.getBoundingBox())) {
            isColliding = false;
        }
    }

    setPosition(sf::Vector2f(left, top));
}

sf::FloatRect CollidableEntity::getBoundingBox() const {
    return this->getGlobalBounds();
}
