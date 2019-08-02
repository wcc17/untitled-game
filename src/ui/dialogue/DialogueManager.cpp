#include "../../../includes/ui/dialogue/DialogueManager.h"

Logger DialogueManager::logger("DialogueManager");
const float DIALOGUE_TEXT_WIDTH_DIVISOR = 14;
const float DIALOGUE_TEXT_HEIGHT_DIVISOR = 3;

DialogueManager::DialogueManager() : defaultDialogueEvent("default") { }

void DialogueManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, sf::Font* font, float windowScale) {
    this->eventBus = eventBus;

    this->windowScale = windowScale;
    this->printableDialogueText.initialize(font, windowScale);

    Dialogue defaultDialogue("Nothing to see here.", "");
    defaultDialogueEvent.addDialogue(defaultDialogue);

    //TODO: the dialogueBox sprite should probably be loaded from a tile map. Would be a difficult change to make though
    this->dialogueBoxSprite.setTexture(*texture);
    this->dialogueBoxSprite.scale(0.33f, 0.33f); //TODO: this shouldn't be done this way. Dialog box should just be drawn at the right size for the view
}

void DialogueManager::update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime) {
    switch(dialogueState) {
        case DialogueState::STATE_READY:
            setPositionsOnDialogueIsActive(renderTexture, view);
            break;
        case DialogueState::STATE_ACTIVE:
            printableDialogueText.update(deltaTime);
            break;
        case DialogueState::STATE_INACTIVE:
            break;
    }
}

void DialogueManager::drawToRenderTexture(sf::RenderTexture* renderTexture) {
    if(dialogueState == STATE_ACTIVE) {
        renderTexture->draw(dialogueBoxSprite);

        //draw to default view and then switch back to whatever view renderTexture was using before
        const sf::View& v = renderTexture->getView();
        renderTexture->setView(renderTexture->getDefaultView());
        renderTexture->draw(printableDialogueText); //TODO: who should know that text should be drawn to the default view? The manager or the text itself?
        renderTexture->setView(v);
    }
}

void DialogueManager::setPositionsOnDialogueIsActive(sf::RenderTexture& renderTexture, sf::View& view) {
    updateDialogueBoxPosition(view.getCenter(), view.getSize());
    updateDialogueTextPosition(renderTexture, view);
    dialogueState = STATE_ACTIVE;
}

void DialogueManager::updateDialogueBoxPosition(const sf::Vector2f& viewCenter, const sf::Vector2f& viewSize) {
    float dialogueBoxX = viewCenter.x - (viewSize.x / 2) + (viewSize.x - dialogueBoxSprite.getGlobalBounds().width)/2;
    float dialogueBoxY = viewCenter.y + (viewSize.y / 2) - dialogueBoxSprite.getGlobalBounds().height;
    dialogueBoxSprite.setPosition(dialogueBoxX, dialogueBoxY);
}

void DialogueManager::updateDialogueTextPosition(sf::RenderTexture& renderTexture, sf::View& view) {
    sf::Vector2i coordsToPixel = renderTexture.mapCoordsToPixel(dialogueBoxSprite.getPosition(), view);
    coordsToPixel.x = coordsToPixel.x + (dialogueBoxSprite.getTextureRect().width / (DIALOGUE_TEXT_WIDTH_DIVISOR/windowScale));
    coordsToPixel.y = coordsToPixel.y + (dialogueBoxSprite.getTextureRect().height / (DIALOGUE_TEXT_HEIGHT_DIVISOR/windowScale));
    printableDialogueText.setPosition(coordsToPixel.x, coordsToPixel.y);
}

void DialogueManager::onControllerActionEvent() {
    if(dialogueState == STATE_ACTIVE) {
        if(!printableDialogueText.isDialogueFinishedPrinting()) {
            printableDialogueText.onControllerEvent();
        } else {
            closeDialogue();
        }

    }
}

void DialogueManager::onOpenDialogueEvent(OpenDialogueEvent* event) {
    logger.logDebug("ready to handle the dialogue box in DialogueManager");
    entityPlayerInteractedWith = event->interactedWith;

    DialogueEvent dialogueEvent = getDialogueEventForEntityWithName(entityPlayerInteractedWith.getName());
    printableDialogueText.startNewDialogueEvent(dialogueEvent);

    dialogueState = STATE_READY;
}

void DialogueManager::closeDialogue() {
    dialogueState = STATE_INACTIVE;
    printableDialogueText.reset();
    eventBus->publish(new CloseDialogueEvent(entityPlayerInteractedWith));
}

DialogueEvent DialogueManager::getDialogueEventForEntityWithName(std::string entityName) {
    for(int i = 0; i < entityDialogueEvents.size(); i++) {
        if(entityDialogueEvents[i].getName() == entityName) {
            return entityDialogueEvents[i];
        }
    }

    return defaultDialogueEvent;
}

void DialogueManager::setEntityDialogueEvents(std::vector<DialogueEvent> entityDialogueEvents) {
    this->entityDialogueEvents = entityDialogueEvents;
}

bool DialogueManager::isDialogueActive() {
    return !(dialogueState == STATE_INACTIVE); //dialogue is active as long as state != STATE_INACTIVE
}

void DialogueManager::release(TextureManager &textureManager) {
    //TODO: need to release PrintableDialogueText?
    textureManager.releaseTexture(AssetPath::DIALOGUE_BOX_TEXTURE);
}
