#include "../../../includes/ui/dialogue/Dialogue.h"

Dialogue::Dialogue(std::string first, std::string second): first(first), second(second) {
    this->first += "\n";
}

std::string& Dialogue::getCurrentDialoguePiece() {
    return (first.length() > 0) ? first : second;
}

bool Dialogue::dialogueDone() {
    //if one still has characters, dialogue is not done
    return (first.length() == 0 && second.length() == 0);
}