#include "../../../includes/entity/character/MovableEntity.h"

void MovableEntity::initialize(float moveSpeed) {
    this->moveSpeed = moveSpeed;
}

void MovableEntity::update(sf::Time deltaTime) {
}

void MovableEntity::onMoveEvent(MoveDirection direction) {
    switch(state) {
        case STATE_STANDING:
            break;
        case STATE_MOVING:
            break;
        case STATE_MOVING_TO_GOAL:
            break;
    }

            /**
             * Player starts out standing
             * As a movement button is being pressed:
             *  1. the state changes to "STATE_MOVING"
             *  2. a goal is set depending on the direction (the next closest tile)
             *  3. the player moves to that goal
             * If no movement button is being pressed
             *  1. if no goal has been reached, the state changes to "STATE_MOVING_TO_GOAL"
             *      a. Entity will keep moving in the most previous direction until goal is reached
             *  2. if we're at a goal, the state changes to "STATE_STANDING"
             *      a. previous direction is cleared, we don't care about it anymore
             *
             *  Player > Character Entity > AnimatedEntity, Collidable
             *  Character Entity has state?
             *
             *  Going to try with current configuration for now. I don't think the states will be that complex? The player can't really do more than one thing at a time
             *
             *  Should probably move all PlayerManager movement stuff into MovableEntity and then set the view from the player rather than setting the player position from the view.
             *  Because NPC will basically do the same things movement wise as the player
             */

    currentDirection = direction;

    resetMovement();
    switch(currentDirection) {
        case MoveDirection::UP:
            movement.y -= moveSpeed;
            break;
        case MoveDirection::LEFT:
            movement.x -= moveSpeed;
            break;
        case MoveDirection::DOWN:
            movement.y += moveSpeed;
            break;
        case MoveDirection::RIGHT:
            movement.x += moveSpeed;
            break;
        case MoveDirection::NONE:
            break;
        default:
            break;
    }
}

void MovableEntity::resetMovement() {
    movement.x = 0;
    movement.y = 0;
}

sf::Vector2f MovableEntity::getMovement() {
    return this->movement;
}