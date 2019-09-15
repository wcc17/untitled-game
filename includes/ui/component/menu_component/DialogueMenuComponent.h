#ifndef NEWNEW_DIALOGUEMENUCOMPONENT_H
#define NEWNEW_DIALOGUEMENUCOMPONENT_H

#include <string>
#include "../MenuComponent.h"

class DialogueMenuComponent : public MenuComponent {
public:
    void updateMenuOption(std::string textToDraw);
};


#endif //NEWNEW_DIALOGUEMENUCOMPONENT_H
