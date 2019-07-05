#include "../../../includes/entity/character/EntityCollidable.h"

void EntityCollidable::initialize(const Collidable& collidable) {
    setName(collidable.getName());
    setType(collidable.getType());
    setBoundingBox(collidable.getBoundingBox());
}

sf::Vector2f EntityCollidable::getFixedPositionAfterCollision(const Collidable& collidedWith, MoveDirection entityDirection) {
    bool isColliding = true;
    int left = getBoundingBox().left;
    int top = getBoundingBox().top;
    sf::FloatRect newBounds;
    while(isColliding) {
        if(entityDirection == MoveDirection::NONE) {
            //NOTE: If an entity is moving into this one while its standing still, the entity will handle the collision. Otherwise this should never happen
            printf("EntityCollidable::getFixedPositionAfterCollision: possible error with %s collision - the entity didn't move into this collision so theres no way to move him out\n", getName().c_str());
            isColliding = false;
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

        newBounds = sf::FloatRect(left, top, getBoundingBox().width, getBoundingBox().height);
        if(!newBounds.intersects(collidedWith.getBoundingBox())) {
            isColliding = false;
        }
    }

    setBoundingBox(newBounds);
    return sf::Vector2f(left, top);
}
bool EntityCollidable::isFacingCollidableInVicinity(MoveDirection facingDirection, Collidable& collidableInVicinity) {
    sf::FloatRect roundedEntityBounds = getBoundingBox();
    sf::FloatRect collidableRect = collidableInVicinity.getBoundingBox();
    switch(facingDirection) {
        case MoveDirection::DOWN:
        case MoveDirection::UP:
            if(roundedEntityBounds.left == collidableRect.left //entity's left side lines up with the left side of the collidable
               || ((roundedEntityBounds.left > collidableRect.left) && ((roundedEntityBounds.left + roundedEntityBounds.width) <= (collidableRect.left + collidableRect.width))) //entity is somewhere completely in the middle of collidable
               || ((roundedEntityBounds.left + roundedEntityBounds.width) == (collidableRect.left + collidableRect.width))) { //entity's right side lines up with the right side of the collidable
                return true;
            }
            return false;

        case MoveDirection::LEFT:
        case MoveDirection::RIGHT:
            if(roundedEntityBounds.top == collidableRect.top //entity's top side lines up with the top side of the collidable
               || ((roundedEntityBounds.top > collidableRect.top) && ((roundedEntityBounds.top + roundedEntityBounds.height) <= (collidableRect.top + collidableRect.height))) //entity is somewhere completely in the middle of collidable
               || ((roundedEntityBounds.top + roundedEntityBounds.height) == (collidableRect.top + collidableRect.height))) { //entity's bottom side lines up with the bottom side of the collidable
                return true;
            }
            return false;
        default:
            printf("EntityCollidable.isEntityRectAlignedWithCollidableRect should not be passed anything other than up, down, left, right\n");
            return false;
    }
}

sf::FloatRect EntityCollidable::getVicinityBounds() const {
    sf::FloatRect vicinityBounds = sf::FloatRect(getBoundingBox().left - vicinityBoundsOffset,
                                                 getBoundingBox().top - vicinityBoundsOffset,
                                                 getBoundingBox().width + (vicinityBoundsOffset*2),
                                                 getBoundingBox().height + (vicinityBoundsOffset*2));
    return vicinityBounds;
}

std::vector<std::shared_ptr<Collidable>> EntityCollidable::getCollidablesInVicinity() {
    return collidablesInVicinity;
}

void EntityCollidable::addCollidableInVicinity(std::shared_ptr<Collidable> collidable) {
    collidablesInVicinity.push_back(collidable);
}

void EntityCollidable::clearCollidablesInVicinity() {
    collidablesInVicinity.clear();
}

void EntityCollidable::setVicinityBoundsOffset(int vicinityBoundsOffset) {
    this->vicinityBoundsOffset = vicinityBoundsOffset;
}