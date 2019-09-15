#ifndef NEWNEW_PARTYMENUCOMPONENT_H
#define NEWNEW_PARTYMENUCOMPONENT_H

#include "../MenuComponent.h"

class PartyMenuComponent : public MenuComponent {

public:
    void initialize(
            sf::Font* font,
            float windowScale,
            std::string name,
            ObjectType type,
            sf::Texture* texture,
            ScreenPosition screenPosition,
            sf::Vector2f textOffset) override;
private:
    std::vector<std::string> partyMemberNames;
    void buildMenuOptions();
};

#endif //NEWNEW_PARTYMENUCOMPONENT_H
