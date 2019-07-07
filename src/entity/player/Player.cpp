#include "../../../includes/entity/player/Player.h"

const float PLAYER_WIDTH = 16.f;
const float PLAYER_HEIGHT = 16.f;
const float PLAYER_FRAME_TIME =  0.16f;
const float MOVEMENT_SPEED = 80.f;
const int VICINITY_BOUNDS_OFFSET = 4;

void Player::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, const Collidable& collidable) {
    sf::Sprite::setTexture(*texture);

    entityMovement.initialize(collidable.getName(), MOVEMENT_SPEED);
    currentDirection = MoveDirection::NONE;

    this->state = STATE_STANDING;
    this->entityCollidable.initialize(collidable);
    this->entityCollidable.setVicinityBoundsOffset(VICINITY_BOUNDS_OFFSET);
    sf::Sprite::setPosition(sf::Vector2f(collidable.getBoundingBox().left, collidable.getBoundingBox().top));

    entityAnimation.setFrameTime(sf::seconds(PLAYER_FRAME_TIME));
    initializeAnimations();

    this->eventBus = eventBus;

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
    sf::Vector2f newPosition = getPosition();
    entityMovement.handleStanding(deltaTime, state, currentDirection, newPosition);
    setPosition(newPosition);

    handleState(deltaTime);
}

void Player::handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    sf::Vector2f newPosition = getPosition();
    entityMovement.handleMoving(deltaTime, mapTileSize, state, currentDirection, newPosition);
    setPosition(newPosition);

    handleState(deltaTime);
}

void Player::handleInteractingState() {
    resetAfterFrame();
}

void Player::handleState(sf::Time deltaTime) {
    entityAnimation.update(deltaTime, currentDirection);
    handleActionButtonPressed();
    resetAfterFrame();
    adjustPlayerAndViewPositions();
    sf::Sprite::setTextureRect(entityAnimation.getTextureRect());
    this->entityCollidable.setBoundingBox(sf::FloatRect(getPosition().x, getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT));
}

void Player::adjustPlayerAndViewPositions() {
    eventBus->publish(new PlayerPositionChangeEvent(sf::Sprite::getGlobalBounds()));
    roundPosition();
}

void Player::handleActionButtonPressed() {
    if(actionButtonPressed) {
        MoveDirection currentlyFacingDirection = entityMovement.getLastFacingDirection();

        for(std::shared_ptr<Collidable> collidable : entityCollidable.getCollidablesInVicinity()) {
            if(entityCollidable.isFacingCollidableInVicinity(currentlyFacingDirection, *collidable)) {
                state = STATE_INTERACTING;
                entityAnimation.stop();
                eventBus->publish(new OpenDialogueEvent(getGlobalBounds(), *collidable, currentlyFacingDirection));
                break;
            }
        }
    }
}

void Player::onControllerMoveEvent(ControllerMoveEvent* event) {
    currentDirection = event->direction;
}

void Player::onControllerActionEvent(ControllerActionEvent* event) {
    this->actionButtonPressed = (state != STATE_INTERACTING);
}

void Player::onVicinityCollisionEvent(PlayerVicinityCollisionEvent* event) {
    entityCollidable.addCollidableInVicinity(event->collidedWith);
}

void Player::onCloseDialogueEvent(CloseDialogueEvent* event) {
    state = STATE_STANDING;
}

void Player::onCollisionEvent(PlayerCollisionEvent* event) {
    setPosition(entityCollidable.getFixedPositionAfterCollision(event->collidedWith, currentDirection));
    adjustPlayerAndViewPositions();
}

void Player::resetAfterFrame() {
    entityCollidable.clearCollidablesInVicinity();
    actionButtonPressed = false;
}

void Player::roundPosition() {
    setPosition(std::round(getPosition().x), std::round(getPosition().y));
}

EntityCollidable Player::getEntityCollidable() {
    return entityCollidable;
}

void Player::initializeAnimations() {
    //TODO: EVERYTHING needs to be multiples of tile size, including the character textures (its frames). Should there be a check to ensure this is happening so that I don't forget? How can I get the tile size here? Also NpcEntity
    //TODO: I don't like that the animations are public members of EntityAnimation. The way animations are handled needs to be refactored
    entityAnimation.walkingAnimationDown.setSpriteSheet(*this->getTexture());
    entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
    entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(PLAYER_WIDTH, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
    entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(PLAYER_WIDTH*2, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
    entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(PLAYER_WIDTH*3, 0, PLAYER_WIDTH, PLAYER_HEIGHT));

    entityAnimation.walkingAnimationRight.setSpriteSheet(*this->getTexture());
    entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(0, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
    entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
    entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(PLAYER_WIDTH*2, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
    entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(PLAYER_WIDTH*3, PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));

    entityAnimation.walkingAnimationUp.setSpriteSheet(*this->getTexture());
    entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(0, PLAYER_HEIGHT*2, PLAYER_WIDTH, PLAYER_HEIGHT));
    entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(PLAYER_WIDTH, PLAYER_HEIGHT*2, PLAYER_WIDTH, PLAYER_HEIGHT));
    entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(PLAYER_WIDTH*2, PLAYER_HEIGHT*2, PLAYER_WIDTH, PLAYER_HEIGHT));
    entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(PLAYER_WIDTH*3, PLAYER_HEIGHT*2, PLAYER_WIDTH, PLAYER_HEIGHT));

    entityAnimation.walkingAnimationLeft.setSpriteSheet(*this->getTexture());
    entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(0, PLAYER_HEIGHT*3, PLAYER_WIDTH, PLAYER_HEIGHT));
    entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(PLAYER_WIDTH, PLAYER_HEIGHT*3, PLAYER_WIDTH, PLAYER_HEIGHT));
    entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(PLAYER_WIDTH*2, PLAYER_HEIGHT*3, PLAYER_WIDTH, PLAYER_HEIGHT));
    entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(PLAYER_WIDTH*3, PLAYER_HEIGHT*3, PLAYER_WIDTH, PLAYER_HEIGHT));

    entityAnimation.turnToFaceDirection(MoveDirection::DOWN);
}