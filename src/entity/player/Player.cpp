#include "../../../includes/entity/player/Player.h"

const float PLAYER_WIDTH = 16.f;
const float PLAYER_HEIGHT = 16.f;
const float PLAYER_FRAME_TIME =  0.16f;
const float MOVEMENT_SPEED = 80.f;
const int VICINITY_BOUNDS_OFFSET = 4;
Logger Player::logger("Player");

void Player::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture) {
    sf::Sprite::setTexture(*texture);
    this->eventBus = eventBus;
    this->state = STATE_STANDING;
    this->currentDirection = MoveDirection::NONE;

    entityAnimation.setFrameTime(sf::seconds(PLAYER_FRAME_TIME));
    initializeAnimations();

    eventBus->subscribe(this, &Player::onControllerMoveEvent);
    eventBus->subscribe(this, &Player::onControllerActionEvent);
    eventBus->subscribe(this, &Player::onVicinityCollisionEvent);
    eventBus->subscribe(this, &Player::onCloseDialogueEvent);
    eventBus->subscribe(this, &Player::onCollisionEvent);
    eventBus->subscribe(this, &Player::onDoorCollisionEvent);
}

void Player::initializeForScene(const Collidable& collidable) {
    entityMovement.initialize(collidable.getName(), MOVEMENT_SPEED);
    entityCollidable.initialize(collidable);
    entityCollidable.setVicinityBoundsOffset(VICINITY_BOUNDS_OFFSET);
    sf::Sprite::setPosition(sf::Vector2f(collidable.getBoundingBox().left, collidable.getBoundingBox().top));
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
        case STATE_PLAYER_INTERACTING_WITH_UI:
            handleInteractingState();
            break;
    }
}

void Player::handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    sf::Vector2f newPosition = getPosition();
    entityMovement.handleStanding(deltaTime, state, currentDirection, newPosition);
    setPosition(newPosition);

    handleState(deltaTime);

    if((fmod(getPosition().x, mapTileSize.x) != 0 || fmod(getPosition().y,mapTileSize.y) != 0) && state == STATE_STANDING) {
        logger.logError("handleStandingState(). Player has invalid position not divisible by mapTileSize");
    }
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
    MoveDirection currentlyFacingDirection = entityMovement.getLastFacingDirection();

    for(std::shared_ptr<Collidable> collidable : entityCollidable.getCollidablesInVicinity()) {
        if(entityCollidable.isFacingCollidableInVicinity(currentlyFacingDirection, *collidable)) {
            state = STATE_PLAYER_INTERACTING_WITH_UI;
            entityAnimation.stop();
            eventBus->publish(new OpenDialogueEvent(getGlobalBounds(), *collidable, currentlyFacingDirection));
            break;
        }
    }
}

void Player::onControllerMoveEvent(ControllerMoveEvent* event) {
    currentDirection = event->direction;
}

void Player::onControllerActionEvent(ControllerActionEvent* event) {
    if(state != STATE_PLAYER_INTERACTING_WITH_UI) {
        handleActionButtonPressed();
    }
}

void Player::onVicinityCollisionEvent(PlayerVicinityCollisionEvent* event) {
    entityCollidable.addCollidableInVicinity(event->collidedWith);
}

void Player::onCloseDialogueEvent(CloseDialogueEvent* event) {
    state = STATE_STANDING;
}

void Player::onCollisionEvent(PlayerCollisionEvent* event) {
    setPosition(entityCollidable.getFixedPositionAfterCollision(event->collidedWith));
    adjustPlayerAndViewPositions();
}

void Player::onDoorCollisionEvent(PlayerDoorCollisionEvent* event) {
    eventBus->publish(new ChangeSceneEvent(event->collidedWith));
}

void Player::resetAfterFrame() {
    entityCollidable.clearCollidablesInVicinity();
}

void Player::roundPosition() {
    setPosition(std::round(getPosition().x), std::round(getPosition().y));
}

EntityCollidable Player::getEntityCollidable() {
    return entityCollidable;
}

MoveDirection Player::getLastFacingDirection() {
    return entityMovement.getLastFacingDirection();
}

bool Player::isMoving() {
    return state == STATE_MOVING;
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