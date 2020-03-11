#ifndef NEWNEW_DIALOGUE_H
#define NEWNEW_DIALOGUE_H

#include <string>

class Dialogue {
public:
    Dialogue(std::string first, std::string second);
    std::string& getCurrentDialoguePiece();
    bool dialogueDone();
    std::string getFirstDialoguePiece();
    std::string getSecondDialoguePiece();
    void setFirstDialoguePiece(std::string piece);
    void setSecondDialoguePiece(std::string piece);

private:
    std::string first;
    std::string second;
};


#endif //NEWNEW_DIALOGUE_H
