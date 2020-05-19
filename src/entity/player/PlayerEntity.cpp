#include "../../../includes/entity/player/PlayerEntity.h"

const float PLAYER_WIDTH = 16.f;
const float PLAYER_HEIGHT = 16.f;
const float PLAYER_FRAME_TIME =  0.16f;
const float MOVEMENT_SPEED = 80.f;
const int VICINITY_BOUNDS_OFFSET = 4;
Logger PlayerEntity::logger("PlayerEntity");

void PlayerEntity::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture) {
    sf::Sprite::setTexture(*texture);
    this->eventBus = eventBus;
    this->state = STATE_STANDING;
    this->currentDirection = MoveDirection::NONE;

    entityAnimation.setFrameTime(sf::seconds(PLAYER_FRAME_TIME));
    initializeAnimations();

    eventBus->subscribe(this, &PlayerEntity::onControllerMoveEvent, "PlayerEntity");
    eventBus->subscribe(this, &PlayerEntity::onControllerActionEvent, "PlayerEntity");
    eventBus->subscribe(this, &PlayerEntity::onVicinityCollisionEvent, "PlayerEntity");
    eventBus->subscribe(this, &PlayerEntity::onCloseDialogueEvent, "PlayerEntity");
    eventBus->subscribe(this, &PlayerEntity::onCollisionEvent, "PlayerEntity");
    eventBus->subscribe(this, &PlayerEntity::onDoorCollisionEvent, "PlayerEntity");
    eventBus->subscribe(this, &PlayerEntity::onPlayerAndNpcCollisionEvent, "PlayerEntity");
}

void PlayerEntity::initializeForScene(const Collidable& collidable, const sf::Vector2u& mapTileSize) {
    this->mapTileSize = mapTileSize;
    entityMovement.initialize(collidable.getName(), MOVEMENT_SPEED);
    entityCollidable.initialize(collidable);
    entityCollidable.setVicinityBoundsOffset(VICINITY_BOUNDS_OFFSET);
    sf::Sprite::setPosition(sf::Vector2f(collidable.getBoundingBox().left, collidable.getBoundingBox().top));
    adjustPlayerAndViewPositions();
}

void PlayerEntity::update(sf::Time deltaTime) {
    switch(state) {
        case STATE_STANDING:
            handleStandingState(deltaTime);
            break;
        case STATE_MOVING:
            handleMovingState(deltaTime);
            break;
        case STATE_PLAYER_INTERACTING_WITH_UI:
            handleInteractingState();
            break;
        case STATE_PLAYER_DONE_WITH_UI:
            handleDoneInteractingState();
            break;
    }
}

void PlayerEntity::handleStandingState(sf::Time deltaTime) {
    sf::Vector2f newPosition = getPosition();
    entityMovement.handleStanding(deltaTime, state, currentDirection, newPosition);
    setPosition(newPosition);

    handleState(deltaTime);

    if((fmod(getPosition().x, mapTileSize.x) != 0 || fmod(getPosition().y,mapTileSize.y) != 0) && state == STATE_STANDING) {
        logger.logError("handleStandingState(). PlayerEntity has invalid position not divisible by mapTileSize");
    }
}

void PlayerEntity::handleMovingState(sf::Time deltaTime) {
    sf::Vector2f newPosition = getPosition();
    entityMovement.handleMoving(deltaTime, mapTileSize, state, currentDirection, newPosition);
    setPosition(newPosition);

    handleState(deltaTime);
}

void PlayerEntity::handleInteractingState() {
    resetAfterFrame();
}

void PlayerEntity::handleDoneInteractingState() {
    resetAfterFrame();
    state = STATE_STANDING;
}

void PlayerEntity::handleState(sf::Time deltaTime) {
    entityAnimation.update(deltaTime, currentDirection);
    resetAfterFrame();
    adjustPlayerAndViewPositions(); //TODO: this does not need to run every single frame
    sf::Sprite::setTextureRect(entityAnimation.getTextureRect());
    this->entityCollidable.setBoundingBox(sf::FloatRect(getPosition().x, getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT));
}

void PlayerEntity::adjustPlayerAndViewPositions() {
    eventBus->publish(new PlayerPositionChangeEvent(sf::Sprite::getGlobalBounds()));
    roundPosition();
}

void PlayerEntity::handleActionButtonPressed() {
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

void PlayerEntity::onControllerMoveEvent(ControllerMoveEvent* event) {
    currentDirection = event->direction;
}

void PlayerEntity::onControllerActionEvent(ControllerActionEvent* event) {
    if(state == STATE_MOVING || state == STATE_STANDING) {
        handleActionButtonPressed();
    }
}

void PlayerEntity::onVicinityCollisionEvent(PlayerVicinityCollisionEvent* event) {
    entityCollidable.addCollidableInVicinity(event->collidedWith);
}

void PlayerEntity::onCloseDialogueEvent(CloseDialogueEvent* event) {
    state = STATE_PLAYER_DONE_WITH_UI;
}

void PlayerEntity::onCollisionEvent(PlayerCollisionEvent* event) {
    setPosition(event->newPlayerPosition);
    adjustPlayerAndViewPositions();
}

void PlayerEntity::onDoorCollisionEvent(PlayerDoorCollisionEvent* event) {
    //any door object on the tmx tiled map should have a name that designates the new map that the door leads to
    eventBus->publish(new ChangeSceneToNewMapEvent(event->collidedWith.getName()));
}

void PlayerEntity::onPlayerAndNpcCollisionEvent(PlayerAndNpcCollisionEvent* event) {
    if(event->npc.isNpcAggressive()) {
        eventBus->publish(new ChangeSceneToBattleEvent(event->npc));
    }
}

void PlayerEntity::resetAfterFrame() {
    entityCollidable.clearCollidablesInVicinity();
}

void PlayerEntity::roundPosition() {
    setPosition(std::round(getPosition().x), std::round(getPosition().y));
}

EntityCollidable PlayerEntity::getEntityCollidable() const {
    return entityCollidable;
}

MoveDirection PlayerEntity::getLastFacingDirection() const {
    return entityMovement.getLastFacingDirection();
}

void PlayerEntity::release() {
    eventBus->unsubscribeInstanceFromAllEventTypes(this);
}

void PlayerEntity::initializeAnimations() {
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