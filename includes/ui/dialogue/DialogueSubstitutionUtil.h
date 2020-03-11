#ifndef NEWNEW_DIALOGUESUBSTITUTIONUTIL_H
#define NEWNEW_DIALOGUESUBSTITUTIONUTIL_H


#include <string>
#include <vector>
#include "DialogueEvent.h"

class DialogueSubstitutionUtil {
public:
    DialogueEvent doTextSubstitutionsInDialogueEvent(
            DialogueEvent dialogueEvent,
            std::vector<std::string> textSubstitutions);

private:
    std::vector<Dialogue> doSubstitutionInDialogues(
            std::vector<Dialogue> dialogues,
            std::string textToInsert,
            std::string stringToReplace);
    std::string doSubstitutionInPiece(
            std::string piece,
            std::string textToInsert,
            std::string stringToReplace);
};


#endif //NEWNEW_DIALOGUESUBSTITUTIONUTIL_H
