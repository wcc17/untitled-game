#include "../../../includes/entity/character/EntityCollidable.h"

void EntityCollidable::initialize(const Collidable& collidable) {
    setName(collidable.getName());
    setType(collidable.getType());
    setBoundingBox(collidable.getBoundingBox());
    entityLogger.initialize("EntityCollidable", getName());
}

sf::Vector2f EntityCollidable::getFixedPositionAfterCollision(const Collidable &collidedWith) {
    sf::FloatRect entityBounds = getBoundingBox();
    sf::FloatRect collidedWithBounds = collidedWith.getBoundingBox();
    float difference = 0;
    MoveDirection adjustmentDirection = MoveDirection::NONE;

    setAdjustmentDirectionAndDifference(entityBounds, collidedWithBounds, difference, adjustmentDirection);

    float x = entityBounds.left;
    float y = entityBounds.top;
    sf::Vector2f newPosition = getAdjustedPosition(x, y, difference, adjustmentDirection);

    setBoundingBox(sf::FloatRect(newPosition.x, newPosition.y, getBoundingBox().width, getBoundingBox().height));
    return newPosition;
}

void EntityCollidable::setAdjustmentDirectionAndDifference(const sf::FloatRect& entityBounds,
                                                           const sf::FloatRect& collidedWithBounds,
                                                           float& difference,
                                                           MoveDirection& adjustmentDirection) {
    float left1 = entityBounds.left;
    float right1 = entityBounds.left + entityBounds.width;
    float top1 = entityBounds.top;
    float bottom1 = entityBounds.top + entityBounds.height;

    float left2 = collidedWithBounds.left;
    float right2 = collidedWithBounds.left + collidedWithBounds.width;
    float top2 = collidedWithBounds.top;
    float bottom2 = collidedWithBounds.top + collidedWithBounds.height;

    if(right1 > left2 && left1 < left2 && right1-left2 < bottom1-top2 && right1-left2 < bottom2-top1)
    {
        //entity's right side collided with something, so move it back to the left
        adjustmentDirection = MoveDirection::LEFT;
        difference = right1-left2;
    }
    else if(left1 < right2 && right1 > right2 && right2-left1 < bottom1-top2 && right2-left1 < bottom2-top1)
    {
        //entity's left side collided with something, so move it back to the right
        adjustmentDirection = MoveDirection::RIGHT;
        difference = right2-left1;
    }
    else if(bottom1 > top2 && top1 < top2)
    {
        //bottom of entity collided with something, so move it back up
        adjustmentDirection = MoveDirection::UP;
        difference = bottom1-top2;
    }
    else if(top1 < bottom2 && bottom1 > bottom2)
    {
        //top of entity collided with something, so move it back down
        adjustmentDirection = MoveDirection::DOWN;
        difference = bottom2-top1;
    }
}

sf::Vector2f EntityCollidable::getAdjustedPosition(float x, float y, float difference, MoveDirection adjustmentDirection) {
    switch(adjustmentDirection) {
        case MoveDirection::RIGHT:
            x += difference;
            break;
        case MoveDirection::LEFT:
            x -= difference;
            break;
        case MoveDirection::UP:
            y -= difference;
            break;
        case MoveDirection::DOWN:
            y += difference;
            break;
        case MoveDirection::NONE:
            entityLogger.logError("AdjustmentDirection is set to NONE. How did this happen?");
            break;
    }

    return sf::Vector2f(x, y);
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
            entityLogger.logError("isEntityRectAlignedWithCollidableRect() should not be passed anything other than up, down, left, right");
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