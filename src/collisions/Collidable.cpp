#include "../../includes/collisions/Collidable.h"

Collidable::Collidable() {
    this->name = "";
    this->type = CollidableType::NO_TYPE;
    this->boundingBox = sf::FloatRect({0.f, 0.f, 0.f, 0.f});
}

Collidable::Collidable(std::string name, CollidableType type, sf::Vector2f position, sf::Vector2f size) : boundingBox(position, size) {
    this->name = name;
    this->type = type;
}

//TODO: this can be reused for the NPCs for the most part. Maybe in Collidable?
//TODO: EVERYTHING needs to be multiples of  tile size, including the character textures (its frames). There should be a check to ensure this is happening so that I don't forget
sf::Vector2f Collidable::getFixedPositionAfterCollision(sf::FloatRect entityRect, sf::FloatRect otherRect, sf::Vector2f movement) {
    bool isColliding = true;
    float left = entityRect.left;
    float top = entityRect.top;
    while(isColliding) {
        if(movement.x == 0.f && movement.y == 0.f) {
            printf("error with player collision - the player didn't move into this collision so theres no way to move him out\n");
        }

        if(movement.x > 0.f) {
            left -= 1;
        } else if(movement.x < 0.f) {
            left += 1;
        }

        if(movement.y > 0.f) {
            top -= 1;
        } else if(movement.y < 0.f) {
            top += 1;
        }

        sf::FloatRect newBounds = sf::FloatRect(left, top, entityRect.width, entityRect.height);
        if(!newBounds.intersects(otherRect)) {
            isColliding = false;
        }
    }

    return sf::Vector2f(left, top);
}

void Collidable::updateBoundingBox(sf::FloatRect newBounds) {
    this->boundingBox = newBounds;
}

std::string Collidable::getName() {
    return this->name;
}

CollidableType Collidable::getType() {
    return this->type;
}

sf::FloatRect Collidable::getBoundingBox() {
    return this->boundingBox;
}

