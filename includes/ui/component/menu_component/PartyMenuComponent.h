#ifndef NEWNEW_PARTYMENUCOMPONENT_H
#define NEWNEW_PARTYMENUCOMPONENT_H

#include "../MenuComponent.h"

class PartyMenuComponent : public MenuComponent {

public:
    void initializeMenuComponent(sf::Font* font, float windowScale) override;
private:
    std::vector<std::string> partyMemberNames;
    void buildMenuOptions();
};

#endif //NEWNEW_PARTYMENUCOMPONENT_H
