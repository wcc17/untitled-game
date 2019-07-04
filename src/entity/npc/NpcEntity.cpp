#include "../../../includes/entity/npc/NpcEntity.h"

const float ENTITY_WIDTH = 16.f;
const float ENTITY_HEIGHT = 24.f;
const float ENTITY_MOVEMENT_SPEED = 65.f;
const float ENTITY_FRAME_TIME = 0.16f; //TODO: not sure where I want to load this from yet

void NpcEntity::initialize(sf::Texture* texture, const Collidable& collidable, sf::IntRect moveBoundaries) {
    sf::Sprite::setTexture(*texture);

    this->state = STATE_STANDING;
    this->entityCollidable.setName(collidable.getName());
    this->entityCollidable.setType(collidable.getType());
    this->entityCollidable.setBoundingBox(collidable.getBoundingBox());
    this->setPosition(sf::Vector2f(collidable.getBoundingBox().left, collidable.getBoundingBox().top));

    entityAnimation.setFrameTime(sf::seconds(ENTITY_FRAME_TIME));
    initializeAnimations();

    entityAutonomousMovement.initialize(moveBoundaries, ENTITY_MOVEMENT_SPEED);
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
            handleInteractingState();
            break;
    }
}

void NpcEntity::handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    entityAnimation.update(deltaTime, entityAutonomousMovement.getCurrentDirection());
    roundPosition();

    sf::Vector2f currentPosition = getPosition();
    entityAutonomousMovement.handleStanding(deltaTime, mapTileSize, state, currentPosition);
    setPosition(currentPosition);

    //TODO: DRY
    sf::Sprite::setTextureRect(entityAnimation.getTextureRect());
    this->entityCollidable.setBoundingBox(sf::FloatRect(getPosition().x, getPosition().y, ENTITY_WIDTH, ENTITY_HEIGHT));
}

void NpcEntity::handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    entityAnimation.update(deltaTime, entityAutonomousMovement.getCurrentDirection());

    sf::Vector2f currentPosition = getPosition();
    entityAutonomousMovement.handleMoving(deltaTime, mapTileSize, currentPosition, state);
    setPosition(currentPosition);
    roundPosition();

    //TODO: DRY
    sf::Sprite::setTextureRect(entityAnimation.getTextureRect());
    this->entityCollidable.setBoundingBox(sf::FloatRect(getPosition().x, getPosition().y, ENTITY_WIDTH, ENTITY_HEIGHT));
}

void NpcEntity::handleInteractingState() { }

void NpcEntity::onPlayerInteractionStart(MoveDirection playerFacingDirection) {
    entityAnimation.turnToFaceEntityFacingDirection(playerFacingDirection);
    state = STATE_INTERACTING;
    //TODO: can this put the entity in a weird position? Will it be fixed?
}

void NpcEntity::onPlayerInteractionFinish() {
    state = STATE_STANDING;
    entityAutonomousMovement.setCurrentDirection(MoveDirection::NONE);
    entityAutonomousMovement.resetDistanceMoved();
}

void NpcEntity::onCollisionEvent(const Collidable& collidedWith) {
//    CollidableEntity::fixPositionAfterCollision(collidedWith, currentDirection);
//    roundPosition();
}

void NpcEntity::roundPosition() {
    setPosition(std::round(getPosition().x), std::round(getPosition().y));
}

EntityCollidable NpcEntity::getEntityCollidable() {
    return this->entityCollidable;
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