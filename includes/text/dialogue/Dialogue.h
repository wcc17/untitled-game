#ifndef NEWNEW_DIALOGUE_H
#define NEWNEW_DIALOGUE_H

#include <string>

class Dialogue {
public:
    Dialogue(std::string first, std::string second);
    std::string& getCurrentDialoguePiece();
    bool dialogueDone();

private:
    std::string first;
    std::string second;
};


#endif //NEWNEW_DIALOGUE_H
