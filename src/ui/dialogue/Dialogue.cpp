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

std::string Dialogue::getFirstDialoguePiece() {
    return this->first;
}

std::string Dialogue::getSecondDialoguePiece() {
    return this->second;
}

void Dialogue::setFirstDialoguePiece(std::string piece) {
    this->first = piece;
}

void Dialogue::setSecondDialoguePiece(std::string piece) {
    this->second = piece;
}