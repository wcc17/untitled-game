#include "../../../includes/ui/dialogue/DialogueManager.h"

Logger DialogueManager::logger("DialogueManager");
const float DIALOGUE_TEXT_WIDTH_DIVISOR = 14;
const float DIALOGUE_TEXT_HEIGHT_DIVISOR = 3;

DialogueManager::DialogueManager() : defaultDialogueEvent("default") { }

void DialogueManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, sf::Font* font, float windowScale) {
    this->eventBus = eventBus;

    this->windowScale = windowScale;

    this->dialogueBoxSprite.setTexture(*texture);
    this->dialogueBoxSprite.scale(0.33f, 0.33f); //TODO: this shouldn't be done this way. Dialog box should just be drawn at the right size for the view
    this->dialogueText.setFillColor(sf::Color::Black);
    this->dialogueText.setLineSpacing(1.2f);
    this->dialogueText.setFont(*font);
    this->dialogueText.setCharacterSize(64 * windowScale);

    Dialogue defaultDialogue("Nothing to see here.", "");
    defaultDialogueEvent.addDialogue(defaultDialogue);
}

void DialogueManager::update(sf::RenderWindow* window, sf::View& view, sf::Time deltaTime) {
    if(dialogueIsActive) {
        if(!dialoguePositionSet) {
            setPositionsOnDialogueIsActive(window, view);
        }

        updateText(deltaTime);
    }
}

void DialogueManager::drawToRenderTexture(sf::RenderTexture* renderTexture) {
    if(dialogueIsActive) {
        renderTexture->draw(dialogueBoxSprite);

        //draw to default view and then switch back to whatever view renderTexture was using before
        const sf::View& v = renderTexture->getView();
        renderTexture->setView(renderTexture->getDefaultView());
        renderTexture->draw(dialogueText);
        renderTexture->setView(v);
    }
}

void DialogueManager::setPositionsOnDialogueIsActive(sf::RenderWindow* window, sf::View& view) {
    updateDialogueBoxPosition(view.getCenter(), view.getSize());
    updateDialogueTextPosition(window, view);
    dialoguePositionSet = true;
}

void DialogueManager::updateDialogueBoxPosition(const sf::Vector2f& viewCenter, const sf::Vector2f& viewSize) {
    float dialogueBoxX = viewCenter.x - (viewSize.x / 2) + (viewSize.x - dialogueBoxSprite.getGlobalBounds().width)/2;
    float dialogueBoxY = viewCenter.y + (viewSize.y / 2) - dialogueBoxSprite.getGlobalBounds().height;
    dialogueBoxSprite.setPosition(dialogueBoxX, dialogueBoxY);
}

void DialogueManager::updateDialogueTextPosition(sf::RenderWindow* window, sf::View& view) {
    sf::Vector2i coordsToPixel = window->mapCoordsToPixel(dialogueBoxSprite.getPosition(), view);
    coordsToPixel.x = coordsToPixel.x + (dialogueBoxSprite.getTextureRect().width / (DIALOGUE_TEXT_WIDTH_DIVISOR/windowScale));
    coordsToPixel.y = coordsToPixel.y + (dialogueBoxSprite.getTextureRect().height / (DIALOGUE_TEXT_HEIGHT_DIVISOR/windowScale));
    dialogueText.setPosition(coordsToPixel.x, coordsToPixel.y);
}

void DialogueManager::onControllerActionEvent() {
    if(dialogueIsActive) {
        if(currentDialogueEvent->shouldStartNextDialogue()) {
            startNextDialogue();
        } else if(!currentDialogueEvent->currentDialogueDone()) {
            //player wants to rush the dialogue by mashing action button
            rushDrawText();
        } else if(currentDialogueEvent->isDialogueEventDone()) {
            closeDialogue();
        }
    }
}

void DialogueManager::onOpenDialogueEvent(OpenDialogueEvent* event) {
    dialogueIsActive = true;
    logger.logDebug("ready to handle the dialogue box in DialogueManager");
    entityPlayerInteractedWith = event->interactedWith;
    initializeText();
}

void DialogueManager::closeDialogue() {
    dialogueIsActive = false;
    dialoguePositionSet = false;
    this->stringBeingDrawn = "";
    this->dialogueText.setString("");
    this->currentDialogueEvent.reset();
    eventBus->publish(new CloseDialogueEvent(entityPlayerInteractedWith));
}

void DialogueManager::initializeText() {
    std::string entityName = entityPlayerInteractedWith.getName();

    currentDialogueEvent = nullptr;
    for(int i = 0; i < entityDialogueEvents.size(); i++) {
        if(entityDialogueEvents[i].getName() == entityName) {
            currentDialogueEvent = std::make_unique<DialogueEvent>(entityDialogueEvents[i]);
            break;
        }
    }

    if(currentDialogueEvent == nullptr) {
        currentDialogueEvent = std::make_unique<DialogueEvent>(defaultDialogueEvent);
    }

    currentDialogueEvent->startNextDialogue();
    this->stringBeingDrawn = "";
}

void DialogueManager::updateText(sf::Time deltaTime) {
    if(!currentDialogueEvent->currentDialogueDone()) {
        stringDrawTimer += deltaTime;
        if(stringDrawTimer.asMilliseconds() > 20) {
            drawMoreText();
        }
    }
}

void DialogueManager::drawMoreText() {
    std::string& dialoguePiece = currentDialogueEvent->getCurrentDialoguePiece();

    this->stringBeingDrawn += dialoguePiece[0];
    this->dialogueText.setString(stringBeingDrawn);

    dialoguePiece = dialoguePiece.erase(0, 1); //changing the reference to currentDialoguePiece
    stringDrawTimer = stringDrawTimer.Zero;
}

void DialogueManager::rushDrawText() {
    std::string& dialoguePiece = currentDialogueEvent->getCurrentDialoguePiece();

    this->stringBeingDrawn += dialoguePiece;
    this->dialogueText.setString(stringBeingDrawn);

    dialoguePiece = dialoguePiece.erase(0, dialoguePiece.length()); //changing the reference to currentDialoguePiece
    stringDrawTimer = stringDrawTimer.Zero;
}

void DialogueManager::startNextDialogue() {
    this->stringBeingDrawn = "";
    currentDialogueEvent->startNextDialogue();
}

void DialogueManager::setEntityDialogueEvents(std::vector<DialogueEvent> entityDialogueEvents) {
    this->entityDialogueEvents = entityDialogueEvents;
}

bool DialogueManager::isDialogueActive() {
    return dialogueIsActive;
}

void DialogueManager::release(TextureManager &textureManager) {
    textureManager.releaseTexture(AssetPath::DIALOGUE_BOX_TEXTURE);
}
