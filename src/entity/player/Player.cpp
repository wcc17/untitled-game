#include "../../../includes/entity/player/Player.h"

const float PLAYER_WIDTH = 16.f;
const float PLAYER_HEIGHT = 24.f;
const float PLAYER_FRAME_TIME =  0.16f;
const float MOVEMENT_SPEED = 80.f;
const int VICINITY_BOUNDS_OFFSET = 4;

void Player::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, const Collidable& collidable) {
    AnimatedEntity::initialize(texture);
    MovableEntity::initialize(MOVEMENT_SPEED);

    this->state = STATE_STANDING;
    this->name = collidable.getName();
    this->type = collidable.getType();
    this->setPosition(sf::Vector2f(collidable.getBoundingBox().left, collidable.getBoundingBox().top));

    setFrameTime(sf::seconds(PLAYER_FRAME_TIME));
    initializeAnimations();

    this->eventBus = eventBus;
    this->setVicinityBoundsOffset(VICINITY_BOUNDS_OFFSET);

    eventBus->subscribe(this, &Player::onControllerMoveEvent);
    eventBus->subscribe(this, &Player::onControllerActionEvent);
    eventBus->subscribe(this, &Player::onVicinityCollisionEvent);
    eventBus->subscribe(this, &Player::onCloseDialogueEvent);
    eventBus->subscribe(this, &Player::onCollisionEvent);

    adjustPlayerAndViewPositions();
}

void Player::update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    switch(state) {
        case STATE_STANDING:
            handleStandingState(deltaTime, mapTileSize);
            break;
        case STATE_MOVING:
            handleMovingState(deltaTime, mapTileSize);
            break;
        case STATE_INTERACTING:
            handleInteractingState();
            break;
    }
}

void Player::handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    MovableEntity::handleStandingState(deltaTime, state);
    AnimatedEntity::update(deltaTime, currentDirection);
    handleActionButtonPressed();
    resetAfterFrame();
    adjustPlayerAndViewPositions();
}

void Player::handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    MovableEntity::handleMovingState(deltaTime, mapTileSize, state);
    AnimatedEntity::update(deltaTime, currentDirection);
    handleActionButtonPressed();
    resetAfterFrame();
    adjustPlayerAndViewPositions();
}

void Player::handleInteractingState() {
    resetAfterFrame();
}

void Player::adjustPlayerAndViewPositions() {
    eventBus->publish(new PlayerPositionChangeEvent(getGlobalBounds()));
    roundPosition();
}

void Player::handleActionButtonPressed() {
    if(actionButtonPressed) {
        MoveDirection currentlyFacingDirection = MovableEntity::getCurrentFacingDirection();
        for(std::shared_ptr<Collidable> collidable : collidablesInVicinity) {
            if(CollidableEntity::isFacingCollidableInVicinity(currentlyFacingDirection, *collidable)) {
                state = STATE_INTERACTING;
                AnimatedEntity::stop();
                eventBus->publish(new OpenDialogueEvent(getGlobalBounds(), *collidable, MovableEntity::getCurrentFacingDirection()));
                break;
            }
        }
    }
}

void Player::onControllerMoveEvent(ControllerMoveEvent* event) {
    MovableEntity::setCurrentDirection(event->direction);
}

void Player::onControllerActionEvent(ControllerActionEvent* event) {
    this->actionButtonPressed = (state != STATE_INTERACTING);
}

void Player::onVicinityCollisionEvent(PlayerVicinityCollisionEvent* event) {
    CollidableEntity::addCollidableInVicinity(event->collidedWith);
}

void Player::onCloseDialogueEvent(CloseDialogueEvent* event) {
    state = STATE_STANDING;
}

void Player::onCollisionEvent(PlayerCollisionEvent* event) {
    CollidableEntity::fixPositionAfterCollision(event->collidedWith, currentDirection);
    adjustPlayerAndViewPositions();
}

void Player::resetAfterFrame() {
    CollidableEntity::clearCollidablesInVicinity();
    actionButtonPressed = false;
}

void Player::roundPosition() {
    setPosition(std::round(getPosition().x), std::round(getPosition().y));
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