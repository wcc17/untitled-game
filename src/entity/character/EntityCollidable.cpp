#include "../../../includes/entity/character/EntityCollidable.h"

//TODO: need to wrap logger methods to indicate which entity is printing to the log. See EntityAutonomousMovement. Maybe Collidable should have the wrapped log functions? Idk
Logger EntityCollidable::logger("EntityCollidable");

void EntityCollidable::initialize(const Collidable& collidable) {
    setName(collidable.getName());
    setType(collidable.getType());
    setBoundingBox(collidable.getBoundingBox());
}

sf::Vector2f EntityCollidable::getFixedPositionAfterCollision(const Collidable& collidedWith, MoveDirection entityDirection) {
    int left = getBoundingBox().left;
    int top = getBoundingBox().top;
    sf::FloatRect newBounds;

    //NOTE: assigning left and top to integers effectively rounds the number, so collision has to be checked here again
    newBounds = sf::FloatRect(left, top, getBoundingBox().width, getBoundingBox().height);
    bool isColliding = newBounds.intersects(collidedWith.getBoundingBox());

    while(isColliding) {
        if(entityDirection == MoveDirection::NONE) {
            //NOTE: If an entity is moving into this one while its standing still, the entity will handle the collision. Otherwise this should never happen
            logger.logError("getFixedPositionAfterCollision(): possible error with %s collision - the entity didn't move into this collision so theres no way to move him out", getName().c_str());
            break;
        }

        adjustPositionsByOne(entityDirection, left, top);

        newBounds = sf::FloatRect(left, top, getBoundingBox().width, getBoundingBox().height);
        isColliding = newBounds.intersects(collidedWith.getBoundingBox());
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
            logger.logError("isEntityRectAlignedWithCollidableRect() should not be passed anything other than up, down, left, right");
            return false;
    }
}

void EntityCollidable::adjustPositionsByOne(MoveDirection entityDirection, int& left, int& top) {
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