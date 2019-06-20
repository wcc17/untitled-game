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
bool CollidableEntity::isFacingCollidableInVicinity(MoveDirection facingDirection, Collidable& collidableInVicinity) {
    //TODO: unique_ptr instead of copies?
    sf::FloatRect entityBounds = getGlobalBounds();
    sf::FloatRect collidableBounds = collidableInVicinity.getBoundingBox();

    if(isEntityRectAlignedWithCollidableRect(facingDirection, entityBounds, collidableBounds)) {
        switch(facingDirection) {
            case MoveDirection::DOWN:
                return ((entityBounds.top + entityBounds.height) <= (collidableBounds.top));
            case MoveDirection ::UP:
                return ((entityBounds.top) >= (collidableBounds.top + collidableBounds.height));
            case MoveDirection::LEFT:
                return ((entityBounds.left) >= (collidableBounds.left + collidableBounds.width));
            case MoveDirection::RIGHT:
                return ((entityBounds.left + entityBounds.width) <= (collidableBounds.left));
            default:
                printf("CollidableEntity::isFacingCollidableInVicinity -- player should not be facing in the NONE direction\n");
                return false;
        }
    }

    return false;
}

sf::FloatRect CollidableEntity::getVicinityBounds() const {
    sf::FloatRect vicinityBounds = sf::FloatRect(getGlobalBounds().left - vicinityBoundsOffset,
                                                 getGlobalBounds().top - vicinityBoundsOffset,
                                                 getGlobalBounds().width + (vicinityBoundsOffset*2),
                                                 getGlobalBounds().height + (vicinityBoundsOffset*2));
    return vicinityBounds;
}

void CollidableEntity::addCollidableInVicinity(std::shared_ptr<Collidable> collidable) {
    collidablesInVicinity.push_back(collidable);
}

void CollidableEntity::clearCollidablesInVicinity() {
    collidablesInVicinity.clear();
}

sf::FloatRect CollidableEntity::getBoundingBox() const {
    return this->getGlobalBounds();
}

void CollidableEntity::setVicinityBoundsOffset(int vicinityBoundsOffset) {
    this->vicinityBoundsOffset = vicinityBoundsOffset;
}

bool CollidableEntity::isEntityRectAlignedWithCollidableRect(MoveDirection facingDirection, sf::FloatRect& entityRect, sf::FloatRect& collidableRect) {
    //types not being covered here. I think they're unimportant right now, but could potentially improve this function later on:
    //entity could have his left side in the middle of the collidable, but the right side on the outside of the collidable to the right
    //entity could have his right side in the middle of the collidable, but the left side on the outside of the collidable to the left
    //this works now because everything has a minimum width of 16. If there was something less wide than the player he could still interact with it, but it would look weird

    switch(facingDirection) {
        case MoveDirection::DOWN:
        case MoveDirection::UP:
            if(entityRect.left == collidableRect.left //entity's left side lines up with the left side of the collidable
               || ((entityRect.left > collidableRect.left) && ((entityRect.left + entityRect.width) <= (collidableRect.left + collidableRect.width))) //entity is somewhere completely in the middle of collidable
               || ((entityRect.left + entityRect.width) == (collidableRect.left + collidableRect.width))) { //entity's right side lines up with the right side of the collidable
                return true;
            }
            return false;

        case MoveDirection::LEFT:
        case MoveDirection::RIGHT:
            if(entityRect.top == collidableRect.top //entity's top side lines up with the top side of the collidable
               || ((entityRect.top > collidableRect.top) && ((entityRect.top + entityRect.height) <= (collidableRect.top + collidableRect.height))) //entity is somewhere completely in the middle of collidable
               || ((entityRect.top + entityRect.height) == (collidableRect.top + collidableRect.height))) { //entity's bottom side lines up with the bottom side of the collidable
                return true;
            }
            return false;
    }
}
