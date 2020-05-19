#include "../../includes/collisions/CollisionUtil.h"

Logger CollisionUtil::logger("CollisionManager");

bool CollisionUtil::collisionOccurred(const Collidable& collidable1, const Collidable& collidable2) {
    return ( (collidable1.getName() != collidable2.getName())
             && ( (collidable1.getBoundingBox().intersects(collidable2.getBoundingBox()) )));
}

bool CollisionUtil::playerVicinityCollisionOccurred(const PlayerEntity& player, const Collidable& collidable) {
    const sf::FloatRect& playerVicinityBounds = player.getEntityCollidable().getVicinityBounds();
    return (playerVicinityBounds.intersects(collidable.getBoundingBox()));
}

bool CollisionUtil::playerDoorCollisionOccurred(const PlayerEntity& player, const Collidable& collidable) {
    if(collidable.getType() == ObjectType::DOOR) {
        const sf::FloatRect& playerBounds = player.getEntityCollidable().getBoundingBox();
        const sf::FloatRect& doorBounds = collidable.getBoundingBox();

        switch(player.getLastFacingDirection()) {
            case MoveDirection::DOWN:
            case MoveDirection::UP:
                if( (playerBounds.left >= doorBounds.left)
                    && ((playerBounds.left + playerBounds.width) <= (doorBounds.left + doorBounds.width))) {
                    return true;
                }
                break;
            case MoveDirection::RIGHT:
            case MoveDirection::LEFT:
                if( (playerBounds.top >= doorBounds.top)
                    && ((playerBounds.top + playerBounds.height) <= (doorBounds.top + doorBounds.height))) {
                    return true;
                }
                break;
            default:
                logger.logError("Should be looking at player's entityMovement's previous moving direction instead of its current direction.");
                return false;
        }
    }

    return false;
}

//TODO: needs refactoring in a bad way
void CollisionUtil::fixCollidablePositionAfterCollision(
        const Collidable& collidable1,
        const Collidable& collidable2,
        const sf::Vector2u& mapTileSize,
        sf::Vector2f& collidable1Position,
        sf::Vector2f& collidable2Position) {
    //what side is the collision happening on?
    //two collidables can never be colliding on more than one side (everything is a square)
    //it is possible for two collidables to both not be fixed to the grid. If this happens, move them away from each other in opposite directions

    sf::FloatRect bounds1 = collidable1.getBoundingBox();
    sf::FloatRect bounds2 = collidable2.getBoundingBox();
//    sf::FloatRect bounds1 = sf::FloatRect(1, 0, 8, 8);
//    sf::FloatRect bounds2 = sf::FloatRect(7, 0, 8, 8);

    float left1 = bounds1.left;
    float right1 = bounds1.left + bounds1.width;
    float top1 = bounds1.top;
    float bottom1 = bounds1.top + bounds1.height;

    float left2 = bounds2.left;
    float right2 = bounds2.left + bounds2.width;
    float top2 = bounds2.top;
    float bottom2 = bounds2.top + bounds2.height;

    MoveDirection sideCollisionOccurredOn = MoveDirection::NONE;
    if(right1 > left2 && left1 < left2 && right1-left2 < bottom1-top2 && right1-left2 < bottom2-top1)
    {
        //entity's right side collided with something
        sideCollisionOccurredOn = MoveDirection::RIGHT;
    }
    else if(left1 < right2 && right1 > right2 && right2-left1 < bottom1-top2 && right2-left1 < bottom2-top1)
    {
        //entity's left side collided with something
        sideCollisionOccurredOn = MoveDirection::LEFT;
    }
    else if(bottom1 > top2 && top1 < top2)
    {
        //bottom of entity collided with something
        sideCollisionOccurredOn = MoveDirection::DOWN;
    }
    else if(top1 < bottom2 && bottom1 > bottom2)
    {
        //top of entity collided with something
        sideCollisionOccurredOn = MoveDirection::UP;
    }

    switch(sideCollisionOccurredOn) {
        case MoveDirection::RIGHT: {
            int rightSideCollidable1 = right1;
            int leftSideCollidable2 = left2;
            if ((rightSideCollidable1 % mapTileSize.x) != 0) {
                //fix entity1, moving it to the left
                int old = right1;
                right1 = roundDownToNearestMultipleOf(rightSideCollidable1, mapTileSize.x);
                right1 = abs(old - right1);

                left1 -= right1;
            }
            if ((leftSideCollidable2 % mapTileSize.x) != 0) {
                //fix entity2, move it to the right
                left2 = roundUpToNearestMultipleOf(leftSideCollidable2, mapTileSize.x);
            }
            break;
        }
        case MoveDirection::LEFT: {
            int leftSideCollidable1 = left1;
            int rightSideCollidable2 = right2;
            if ((leftSideCollidable1 % mapTileSize.x) != 0) {
                //fix entity1, move it to the right
                left1 = roundUpToNearestMultipleOf(leftSideCollidable1, mapTileSize.x);
            }
            if ((rightSideCollidable2 % mapTileSize.x) != 0) {
                //fix entity2, move it to the left
                int old = right2;
                right2 = roundDownToNearestMultipleOf(rightSideCollidable2, mapTileSize.x);
                right2 = abs(old - right2);

                left2 -= right2;
            }
            break;
        }
        case MoveDirection::DOWN: {
            int bottomSideCollidable1 = bottom1;
            int topSideCollidable2 = top2;
            if ((bottomSideCollidable1 % mapTileSize.y) != 0) {
                //fix entity1, move it up
                int old = bottom1;
                bottom1 = roundDownToNearestMultipleOf(bottomSideCollidable1, mapTileSize.y);
                bottom1 = abs(old - bottom1);

                top1 -= bottom1;
            }
            if ((topSideCollidable2 % mapTileSize.y) != 0) {
                //fix entity2, move it down
                top2 = roundUpToNearestMultipleOf(topSideCollidable2, mapTileSize.y);
            }
        }
        case MoveDirection::UP: {
            int topSideCollidable1 = top1;
            int bottomSideCollidable2 = bottom2;
            if ((topSideCollidable1 % mapTileSize.y) != 0) {
                //fix entity1, move it down
                top1 = roundUpToNearestMultipleOf(topSideCollidable1, mapTileSize.y);
            }
            if ((bottomSideCollidable2 % mapTileSize.y) != 0) {
                //fix entity2, move it up
                int old = bottom2;
                bottom2 = roundDownToNearestMultipleOf(bottomSideCollidable2, mapTileSize.y);
                bottom2 = abs(old - bottom2);

                top2 -= bottom2;
            }
        }
        default: {
            break;
        }
    }

    collidable1Position = sf::Vector2f(left1, top1);
    collidable2Position = sf::Vector2f(left2, top2);
}

bool CollisionUtil::positionsAreEqual(const sf::Vector2f& position1, const sf::Vector2f& position2) {
    return ((position1.x == position2.x) && (position1.y == position2.y));
}

int CollisionUtil::roundUpToNearestMultipleOf(int numberToRound, int multiple) {
    float x = (float)numberToRound / (float)multiple;
    return ceil(x) * multiple;
}

int CollisionUtil::roundDownToNearestMultipleOf(int numberToRound, int multiple) {
    return (numberToRound - (numberToRound % multiple));
}