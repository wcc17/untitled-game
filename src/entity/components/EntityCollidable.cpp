#include "../../../includes/entity/components/EntityCollidable.h"

void EntityCollidable::initialize(const Collidable& collidable) {
    setName(collidable.getName());
    setType(collidable.getType());
    setBoundingBox(collidable.getBoundingBox());
    entityLogger.initialize("EntityCollidable", getName());
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