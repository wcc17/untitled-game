#include "../../../includes/ui/dialogue/DialogueEvent.h"

DialogueEvent::DialogueEvent(std::string entityName) : currentDialogue(Dialogue("", "")) {
    this->entityName = entityName;
}

void DialogueEvent::addDialogue(Dialogue dialogue) {
    dialogues.push_back(dialogue);
}

std::string& DialogueEvent::getCurrentDialoguePiece() {
    return currentDialogue.getCurrentDialoguePiece();
}

bool DialogueEvent::dialoguesLeftToDraw() {
    return (!dialogues.empty());
}

bool DialogueEvent::currentDialogueDone() {
    //if one still has characters, dialogue is not done
    return currentDialogue.dialogueDone();
}

bool DialogueEvent::shouldStartNextDialogue() {
    return dialoguesLeftToDraw() && currentDialogueDone();
}

bool DialogueEvent::isDialogueEventDone() {
    return !dialoguesLeftToDraw() && currentDialogueDone();
}

void DialogueEvent::startNextDialogue() {
    currentDialogue = dialogues[0];
    dialogues.erase(dialogues.begin());
}

std::string DialogueEvent::getName() {
    return this->entityName;
}