#include "../../../includes/text/dialogue/DialogueEvent.h"

DialogueEvent::DialogueEvent(std::vector<Dialogue> dialogues) {
    this->dialogues = dialogues;
    startNextDialogue();
}

std::string& DialogueEvent::getCurrentDialoguePiece() {
    return currentDialogue->getCurrentDialoguePiece();
}

bool DialogueEvent::dialoguesLeftToDraw() {
    return (!dialogues.empty());
}

bool DialogueEvent::currentDialogueDone() {
    //if one still has characters, dialogue is not done
    return currentDialogue->dialogueDone();
}

bool DialogueEvent::shouldStartNextDialogue() {
    return dialoguesLeftToDraw() && currentDialogueDone();
}

bool DialogueEvent::isDialogueEventDone() {
    return !dialoguesLeftToDraw() && currentDialogueDone();
}

void DialogueEvent::startNextDialogue() {
    currentDialogue.reset();
    currentDialogue = std::make_unique<Dialogue>(dialogues[0]);
    dialogues.erase(dialogues.begin());
}