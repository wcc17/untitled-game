#include "../../../includes/entity/npc/NpcEntity.h"

const float ENTITY_WIDTH = 16.f;
const float ENTITY_HEIGHT = 16.f;
const float ENTITY_MOVEMENT_SPEED = 65.f;
const float ENTITY_FRAME_TIME = 0.16f; //TODO: not sure where I want to load this from yet

void NpcEntity::initialize(sf::Texture* texture, const Collidable& collidable, sf::IntRect moveBoundaries, std::string assetName) {
    sf::Sprite::setTexture(*texture);

    this->assetName = assetName;
    this->state = STATE_STANDING;
    this->entityCollidable.initialize(collidable);
    this->setPosition(sf::Vector2f(collidable.getBoundingBox().left, collidable.getBoundingBox().top));

    entityAnimation.setFrameTime(sf::seconds(ENTITY_FRAME_TIME));
    initializeAnimations();

    entityAutonomousMovement.initialize(entityCollidable.getName(), moveBoundaries, ENTITY_MOVEMENT_SPEED);
    entityLogger.initialize("NpcEntity", entityCollidable.getName());
}

void NpcEntity::update(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    switch(state) {
        case STATE_STANDING:
            handleStandingState(deltaTime, mapTileSize);
            break;
        case STATE_MOVING:
            handleMovingState(deltaTime, mapTileSize);
            break;
        case STATE_INTERACTING:
            handleInteractingState(deltaTime);
            break;
    }
}

void NpcEntity::handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    entityAnimation.update(deltaTime, entityAutonomousMovement.getCurrentDirection());
    sf::Sprite::setTextureRect(entityAnimation.getTextureRect());

    entityAutonomousMovement.handleStanding(deltaTime, mapTileSize, state, getPosition());

    if(fmod(getPosition().x, mapTileSize.x) != 0 || fmod(getPosition().y,mapTileSize.y) != 0) {
        entityLogger.logError("handleStandingState(). NpcEntity has invalid position not divisible by mapTileSize"); //TODO: delete this soon
    }
}

void NpcEntity::handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    entityAnimation.update(deltaTime, entityAutonomousMovement.getCurrentDirection());
    sf::Sprite::setTextureRect(entityAnimation.getTextureRect());

    sf::Vector2f newPosition = entityAutonomousMovement.handleMoveAndReturnPosition(deltaTime, getPosition(), state);
    setEntityPosition(newPosition);
}

void NpcEntity::handleInteractingState(sf::Time deltaTime) {
    entityAnimation.update(deltaTime, entityAutonomousMovement.getCurrentDirection());
}

void NpcEntity::onPlayerInteractionStart(MoveDirection playerFacingDirection) {
    entityAnimation.turnToFaceEntityFacingDirection(playerFacingDirection);
    sf::Sprite::setTextureRect(entityAnimation.getTextureRect());
    stateBeforeInteraction = state;
    state = STATE_INTERACTING;
}

void NpcEntity::onPlayerInteractionFinish() {
    state = stateBeforeInteraction;
}

void NpcEntity::onCollisionEvent(const Collidable& collidedWith) {
    entityLogger.logDebug("npc is colliding with something in onCollisionEvent()");
    sf::Vector2f newPosition = entityCollidable.getFixedPositionAfterCollision(collidedWith, entityAutonomousMovement.getCurrentDirection());
    setEntityPosition(newPosition);
    entityAutonomousMovement.stopMovement(state);
}

void NpcEntity::roundPosition() {
    setPosition(std::round(getPosition().x), std::round(getPosition().y));
}

void NpcEntity::setEntityPosition(const sf::Vector2f& position) {
    setPosition(position);
    this->entityCollidable.setBoundingBox(sf::FloatRect(getPosition().x, getPosition().y, ENTITY_WIDTH, ENTITY_HEIGHT));
    roundPosition();
}

EntityCollidable NpcEntity::getEntityCollidable() {
    return this->entityCollidable;
}

std::string NpcEntity::getAssetName() {
    return this->assetName;
}

//TODO: can this be moved to the header file?
//TODO: EVERYTHING needs to be multiples of  tile size, including the character textures (its frames). There should be a check to ensure this is happening so that I don't forget
void NpcEntity::initializeAnimations() {

    //TODO: these constants are temporary until I figure out where I want to load this information from. Probably from a more specific derived NpcEntity class
    entityAnimation.walkingAnimationDown.setSpriteSheet(*this->getTexture());
    entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(0, 0, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(ENTITY_WIDTH, 0, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(ENTITY_WIDTH*2, 0, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationDown.addFrame(sf::IntRect(ENTITY_WIDTH*3, 0, ENTITY_WIDTH, ENTITY_HEIGHT));

    entityAnimation.walkingAnimationRight.setSpriteSheet(*this->getTexture());
    entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(0, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(ENTITY_WIDTH, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(ENTITY_WIDTH*2, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationRight.addFrame(sf::IntRect(ENTITY_WIDTH*3, ENTITY_HEIGHT, ENTITY_WIDTH, ENTITY_HEIGHT));

    entityAnimation.walkingAnimationUp.setSpriteSheet(*this->getTexture());
    entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(0, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(ENTITY_WIDTH, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(ENTITY_WIDTH*2, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationUp.addFrame(sf::IntRect(ENTITY_WIDTH*3, ENTITY_HEIGHT*2, ENTITY_WIDTH, ENTITY_HEIGHT));

    entityAnimation.walkingAnimationLeft.setSpriteSheet(*this->getTexture());
    entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(0, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(ENTITY_WIDTH, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(ENTITY_WIDTH*2, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));
    entityAnimation.walkingAnimationLeft.addFrame(sf::IntRect(ENTITY_WIDTH*3, ENTITY_HEIGHT*3, ENTITY_WIDTH, ENTITY_HEIGHT));

    entityAnimation.turnToFaceDirection(MoveDirection::DOWN);
}