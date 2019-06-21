#include "../../../includes/entity/player/Player.h"

const float PLAYER_WIDTH = 16.f;
const float PLAYER_HEIGHT = 24.f;
const float PLAYER_FRAME_TIME =  0.16f;
const float MOVEMENT_SPEED = 80.f;
const int VICINITY_BOUNDS_OFFSET = 4;

void Player::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, const Collidable& collidable) {
    CharacterEntity::initialize(texture, MOVEMENT_SPEED, collidable, PLAYER_FRAME_TIME);
    this->eventBus = eventBus;
    this->setVicinityBoundsOffset(VICINITY_BOUNDS_OFFSET);

    eventBus->subscribe(this, &Player::onControllerMoveEvent);
    eventBus->subscribe(this, &Player::onControllerActionEvent);
    eventBus->subscribe(this, &Player::onVicinityCollisionEvent);
    eventBus->subscribe(this, &Player::onCloseDialogueEvent);
}

void Player::update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    handleActionButtonPressed();

    switch(state) {
        case STATE_STANDING:
            handleStandingState(deltaTime);
            break;
        case STATE_MOVING:
            handleMovingState(deltaTime, mapTileSize);
            break;
        case STATE_INTERACTING:
            handleInteractingState();
            break;
    }
}

void Player::handleStandingState(sf::Time deltaTime) {
    MovableEntity::handleStandingState(deltaTime, state);
    AnimatedEntity::update(deltaTime, currentDirection);
}

void Player::handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    MovableEntity::handleMovingState(deltaTime, mapTileSize, state);
    AnimatedEntity::update(deltaTime, currentDirection);
    resetAfterFrame();
}

void Player::handleInteractingState() {
    resetAfterFrame();
}

void Player::fixPositionAfterCollision(const Collidable& collidedWith) {
    //TODO: CollidableEntity code to CharacterEntity
    CollidableEntity::fixPositionAfterCollision(collidedWith, currentDirection);
}

void Player::handleActionButtonPressed() {
    if(actionButtonPressed && state != STATE_INTERACTING) {
        for(std::shared_ptr<Collidable> collidable : collidablesInVicinity) {
            MoveDirection currentlyFacingDirection = MovableEntity::getCurrentFacingDirection();
            if(CollidableEntity::isFacingCollidableInVicinity(currentlyFacingDirection, *collidable)) {
                state = STATE_INTERACTING;
                AnimatedEntity::stop();
                eventBus->publish(new OpenDialogueEvent(getGlobalBounds(), *collidable));
//                eventBus->publish(new TurnEntityTowardCharacterEvent(MovableEntity::getCurrentFacingDirection()));
                break;
            }
        }
    }
}

void Player::onControllerMoveEvent(ControllerMoveEvent* event) {
    MovableEntity::setCurrentDirection(event->direction);
}

void Player::onControllerActionEvent(ControllerActionEvent* event) {
    if(state != STATE_INTERACTING) {
        this->actionButtonPressed = true;
    }
}

void Player::onVicinityCollisionEvent(PlayerVicinityCollisionEvent* event) {
    CollidableEntity::addCollidableInVicinity(event->collidedWith);
}

void Player::onCloseDialogueEvent(CloseDialogueEvent* event) {
    state = STATE_STANDING;
}

void Player::initializeAnimations() {
    //TODO: EVERYTHING needs to be multiples of tile size, including the character textures (its frames). Should there be a check to ensure this is happening so that I don't forget? How can I get the tile size here? Also NpcEntity
    walkingAnimationDown.setSpriteSheet(*this->getTexture());
    walkingAnimationDown.addFrame(sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationDown.addFrame(sf::IntRect(PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationDown.addFrame(sf::IntRect(PLAYER_WIDTH*2, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationDown.addFrame(sf::IntRect(PLAYER_WIDTH*3, 0, PLAYER_WIDTH, PLAYER_HEIGHT));

    walkingAnimationRight.setSpriteSheet(*this->getTexture());
    walkingAnimationRight.addFrame(sf::IntRect(0, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationRight.addFrame(sf::IntRect(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationRight.addFrame(sf::IntRect(PLAYER_WIDTH*2, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationRight.addFrame(sf::IntRect(PLAYER_WIDTH*3, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));

    walkingAnimationUp.setSpriteSheet(*this->getTexture());
    walkingAnimationUp.addFrame(sf::IntRect(0, PLAYER_HEIGHT*2, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationUp.addFrame(sf::IntRect(PLAYER_WIDTH, PLAYER_HEIGHT*2, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationUp.addFrame(sf::IntRect(PLAYER_WIDTH*2, PLAYER_HEIGHT*2, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationUp.addFrame(sf::IntRect(PLAYER_WIDTH*3, PLAYER_HEIGHT*2, PLAYER_WIDTH, PLAYER_HEIGHT));

    walkingAnimationLeft.setSpriteSheet(*this->getTexture());
    walkingAnimationLeft.addFrame(sf::IntRect(0, PLAYER_HEIGHT*3, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationLeft.addFrame(sf::IntRect(PLAYER_WIDTH, PLAYER_HEIGHT*3, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationLeft.addFrame(sf::IntRect(PLAYER_WIDTH*2, PLAYER_HEIGHT*3, PLAYER_WIDTH, PLAYER_HEIGHT));
    walkingAnimationLeft.addFrame(sf::IntRect(PLAYER_WIDTH*3, PLAYER_HEIGHT*3, PLAYER_WIDTH, PLAYER_HEIGHT));

    this->currentAnimation = &walkingAnimationDown;
    setTextureRectBasedOnCurrentFrame();
}

void Player::resetAfterFrame() {
    CollidableEntity::clearCollidablesInVicinity();
    actionButtonPressed = false;
}