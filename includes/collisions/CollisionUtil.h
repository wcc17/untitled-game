#ifndef NEWNEW_COLLISIONUTIL_H
#define NEWNEW_COLLISIONUTIL_H


#include <math.h>
#include "Collidable.h"
#include "../entity/player/PlayerEntity.h"

class CollisionUtil {

public:
    static bool collisionOccurred(const Collidable& collidable1, const Collidable& collidable2);
    static bool playerVicinityCollisionOccurred(const PlayerEntity& player, const Collidable& collidable);
    static bool playerDoorCollisionOccurred(const PlayerEntity& player, const Collidable& collidable);
    static void fixCollidablePositionAfterCollision(
            const Collidable& collidable1,
            const Collidable& collidable2,
            const sf::Vector2u& mapTileSize,
            sf::Vector2f& collidable1Position,
            sf::Vector2f& collidable2Position);
    static bool positionsAreEqual(const sf::Vector2f& position1, const sf::Vector2f& position2);

private:
    static Logger logger;
    static int roundUpToNearestMultipleOf(int numberToRound, int multiple);
    static int roundDownToNearestMultipleOf(int numberToRound, int multiple);
};


#endif //NEWNEW_COLLISIONUTIL_H
