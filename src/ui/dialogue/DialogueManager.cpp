#include "../../../includes/ui/dialogue/DialogueManager.h"

Logger DialogueManager::logger("DialogueManager");

DialogueManager::DialogueManager() : defaultDialogueEvent("default"), currentDialogueEvent("") { }

void DialogueManager::initialize() {
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

void DialogueManager::handleControllerActionButtonPressed() {
    if(dialogueState == STATE_ACTIVE) {
        if(currentDialogueEvent.shouldStartNextDialogue()) {
            startNextDialogue();
        } else if(!currentDialogueEvent.currentDialogueDone()) {
            //player wants to rush the dialogue by mashing action button
            rushDrawText();
        } else if(currentDialogueEvent.isDialogueEventDone()) {
            finishDialogue();
        }
    }
}

void DialogueManager::openDialogue(std::string dialogueTextAssetName) {
    openDialogueWithSubstitutions(dialogueTextAssetName, std::vector<std::string>());
}

void DialogueManager::openDialogueWithSubstitutions(
        std::string dialogueTextAssetName,
        std::vector<std::string> textSubstitutions) {
    logger.logDebug("ready to handle the dialogue box in DialogueManager");
    initializeText(dialogueTextAssetName, textSubstitutions);
    dialogueState = STATE_READY;
    this->currentDialogueIsDone = false;
}

void DialogueManager::finishDialogue() {
    dialogueState = STATE_INACTIVE;
    this->stringToDraw = "";
    this->currentDialogueIsDone = true;
}

void DialogueManager::initializeText(std::string dialogueTextAssetName, std::vector<std::string> textSubstitutions) {
    currentDialogueEvent = assignCurrentDialogueEventForAssetName(dialogueTextAssetName);
    currentDialogueEvent = dialogueSubstitutionUtil.doTextSubstitutionsInDialogueEvent(currentDialogueEvent, textSubstitutions);
    currentDialogueEvent.startNextDialogue();
    this->stringToDraw = "";
}

DialogueEvent DialogueManager::assignCurrentDialogueEventForAssetName(std::string dialogueTextAssetName) {
    for(int i = 0; i < entityDialogueEvents.size(); i++) {
        if(entityDialogueEvents[i].getName() == dialogueTextAssetName) {
            return entityDialogueEvents[i];
        }
    }

    return defaultDialogueEvent;
}

void DialogueManager::updateText(sf::Time deltaTime) {
    if(!currentDialogueEvent.currentDialogueDone()) {
        stringDrawTimer += deltaTime;
        if(stringDrawTimer.asMilliseconds() > 20) {
            drawMoreText();
        }
    }
}

void DialogueManager::drawMoreText() {
    std::string& dialoguePiece = currentDialogueEvent.getCurrentDialoguePiece();
    this->stringToDraw += dialoguePiece[0];

    dialoguePiece = dialoguePiece.erase(0, 1); //changing the reference to currentDialoguePiece
    stringDrawTimer = stringDrawTimer.Zero;
}

void DialogueManager::rushDrawText() {
    std::string& dialoguePiece = currentDialogueEvent.getCurrentDialoguePiece();

    this->stringToDraw += dialoguePiece;

    dialoguePiece = dialoguePiece.erase(0, dialoguePiece.length()); //changing the reference to currentDialoguePiece
    stringDrawTimer = stringDrawTimer.Zero;
}

void DialogueManager::startNextDialogue() {
    this->stringToDraw = "";
    currentDialogueEvent.startNextDialogue();
}

void DialogueManager::setEntityDialogueEvents(std::vector<DialogueEvent> entityDialogueEvents) {
    this->entityDialogueEvents = entityDialogueEvents;
}

std::string DialogueManager::getStringToDraw() {
    return this->stringToDraw;
}

bool DialogueManager::isDialogueEventDone() {
    return this->currentDialogueIsDone;
}