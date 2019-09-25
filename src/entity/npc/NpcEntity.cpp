#include "../../../includes/entity/npc/NpcEntity.h"

void NpcEntity::initialize(
        sf::Texture* texture, const Collidable& collidable,
        sf::IntRect moveBoundaries, std::string assetName,
        bool isAggressive, NpcType npcType) {
    sf::Sprite::setTexture(*texture);

    this->entityWidth = getTexture()->getSize().x / 4;
    this->entityHeight = getTexture()->getSize().y / 4;
    this->npcType = npcType;
    this->isAggressive = isAggressive;
    this->assetName = assetName;
    this->state = STATE_STANDING;

    entityCollidable.initialize(collidable);
    setEntityPosition(sf::Vector2f(collidable.getBoundingBox().left, collidable.getBoundingBox().top));

    initializeAnimations();
    entityAnimation.setFrameTime(sf::seconds(entityFrameTime));

    entityAutonomousMovement.initialize(entityCollidable.getName(), moveBoundaries, entitySpeed, moveDelayRange);
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
        case STATE_PLAYER_INTERACTING_WITH_UI:
            handleInteractingState(deltaTime);
            break;
    }
}

void NpcEntity::handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize) {
    entityAnimation.update(deltaTime, entityAutonomousMovement.getCurrentDirection());
    sf::Sprite::setTextureRect(entityAnimation.getTextureRect());

    entityAutonomousMovement.handleStanding(deltaTime, mapTileSize, state, getPosition());

    if(fmod(getPosition().x, mapTileSize.x) != 0 || fmod(getPosition().y,mapTileSize.y) != 0) {
        entityLogger.logError("handleStandingState(). NpcEntity has invalid position not divisible by mapTileSize");
        setEntityPosition(entityAutonomousMovement.fixInvalidPosition(getPosition(), mapTileSize));
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
    state = STATE_PLAYER_INTERACTING_WITH_UI;
}

void NpcEntity::onPlayerInteractionFinish() {
    state = stateBeforeInteraction;
}

void NpcEntity::onCollisionEvent(const Collidable& collidedWith) {
    entityLogger.logDebug("npc is colliding with something in onCollisionEvent()");
    sf::Vector2f newPosition = entityCollidable.getFixedPositionAfterCollision(collidedWith);
    setEntityPosition(newPosition);
    entityAutonomousMovement.stopMovement(state);
}

void NpcEntity::roundPosition() {
    setPosition(std::round(getPosition().x), std::round(getPosition().y));
}

void NpcEntity::setEntityPosition(const sf::Vector2f& position) {
    setPosition(position);
    this->entityCollidable.setBoundingBox(sf::FloatRect(getPosition().x, getPosition().y, entityWidth, entityHeight));
    roundPosition();
}

EntityCollidable NpcEntity::getEntityCollidable() {
    return this->entityCollidable;
}

std::string NpcEntity::getAssetName() {
    return this->assetName;
}

bool NpcEntity::isMoving() {
    return (this->state == EntityState::STATE_MOVING);
}

bool NpcEntity::isNpcAggressive() {
    return this->isAggressive;
}