#include "../../../includes/ui/dialogue/DialogueSubstitutionUtil.h"

DialogueEvent DialogueSubstitutionUtil::doTextSubstitutionsInDialogueEvent(
        DialogueEvent dialogueEvent,
        std::vector<std::string> textSubstitutions) {
    for(int i = 0; i < textSubstitutions.size(); i++) {
        std::string stringToReplace = "{" + std::to_string(i) + "}";
        std::string textToInsert = textSubstitutions[i];

        std::vector<Dialogue> substitutedDialogues = doSubstitutionInDialogues(dialogueEvent.getDialogues(), textToInsert, stringToReplace);
        dialogueEvent.setDialogues(substitutedDialogues);
    }

    return dialogueEvent;
}

std::vector<Dialogue> DialogueSubstitutionUtil::doSubstitutionInDialogues(
        std::vector<Dialogue> dialogues,
        std::string textToInsert,
        std::string stringToReplace) {
    //each DialogueEvent can have many Dialogues. Each Dialogue can have two pieces of dialogue. Need to cover all of these for each textSubstitution
    for(Dialogue& dialogue : dialogues) {
        //Each dialogue can have up to two pieces. Need to check both of those pieces
        std::string firstPiece = dialogue.getFirstDialoguePiece();
        std::string secondPiece = dialogue.getSecondDialoguePiece();

        dialogue.setFirstDialoguePiece(doSubstitutionInPiece(firstPiece, textToInsert, stringToReplace));
        dialogue.setSecondDialoguePiece(doSubstitutionInPiece(secondPiece, textToInsert, stringToReplace));
    }

    return dialogues;
}

std::string DialogueSubstitutionUtil::doSubstitutionInPiece(
        std::string piece,
        std::string textToInsert,
        std::string stringToReplace) {

    size_t startIndex = 0;
    while((startIndex = piece.find(stringToReplace, startIndex)) != std::string::npos) {
        piece.replace(startIndex, stringToReplace.length(), textToInsert);
        startIndex += textToInsert.length(); // In case 'textToInsert' contains 'stringToReplace', like replacing 'x' with 'yx'
    }

    return piece;
}