#ifndef NEWNEW_MENUMAP_H
#define NEWNEW_MENUMAP_H


#include <tmxlite/Map.hpp>
#include "../asset/AssetPath.h"
#include "../ui/component/MenuComponent.h"
#include "../ui/component/menu_component/PartyMenuComponent.h"
#include "../ui/component/MenuOptionComponent.h"
#include "Map.h"

class MenuMap : public Map {
public:
    MenuMap();
    std::shared_ptr<MenuComponent> loadMenu(std::string menuName, const std::vector<tmx::Object> &objects);

private:
    Logger logger;
};


#endif //NEWNEW_MENUMAP_H
