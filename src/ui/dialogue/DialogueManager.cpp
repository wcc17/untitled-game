#include "../../../includes/ui/dialogue/DialogueManager.h"

Logger DialogueManager::logger("DialogueManager");

DialogueManager::DialogueManager() : defaultDialogueEvent("default") { }

void DialogueManager::initialize(std::shared_ptr<EventBus> eventBus) {
    this->eventBus = eventBus;

    Dialogue defaultDialogue("Nothing to see here.", "");
    defaultDialogueEvent.addDialogue(defaultDialogue);
}

void DialogueManager::update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime) {
    switch(dialogueState) {
        case DialogueState::STATE_READY:
            dialogueState = DialogueState::STATE_ACTIVE;
            break;
        case DialogueState::STATE_ACTIVE:
            updateText(deltaTime);
            break;
        case DialogueState::STATE_INACTIVE:
            break;
    }
}

void DialogueManager::onControllerActionEvent() {
    if(dialogueState == STATE_ACTIVE) {
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
    logger.logDebug("ready to handle the dialogue box in DialogueManager");
    entityPlayerInteractedWith = event->interactedWith;
    initializeText();
    dialogueState = STATE_READY;
}

void DialogueManager::closeDialogue() {
    dialogueState = STATE_INACTIVE;
    this->stringToDraw = "";
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
    this->stringToDraw = "";
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
    this->stringToDraw += dialoguePiece[0];

    dialoguePiece = dialoguePiece.erase(0, 1); //changing the reference to currentDialoguePiece
    stringDrawTimer = stringDrawTimer.Zero;
}

void DialogueManager::rushDrawText() {
    std::string& dialoguePiece = currentDialogueEvent->getCurrentDialoguePiece();

    this->stringToDraw += dialoguePiece;

    dialoguePiece = dialoguePiece.erase(0, dialoguePiece.length()); //changing the reference to currentDialoguePiece
    stringDrawTimer = stringDrawTimer.Zero;
}

void DialogueManager::startNextDialogue() {
    this->stringToDraw = "";
    currentDialogueEvent->startNextDialogue();
}

void DialogueManager::setEntityDialogueEvents(std::vector<DialogueEvent> entityDialogueEvents) {
    this->entityDialogueEvents = entityDialogueEvents;
}

std::string DialogueManager::getStringToDraw() {
    return this->stringToDraw;
}