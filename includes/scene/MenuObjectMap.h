#ifndef NEWNEW_MENUOBJECTMAP_H
#define NEWNEW_MENUOBJECTMAP_H


#include <tmxlite/Map.hpp>
#include "ObjectMap.h"
#include "../../includes/asset/AssetPath.h"
#include "../ui/component/MenuComponent.h"
#include "../ui/component/MenuOptionComponent.h"

class MenuObjectMap : public ObjectMap {
public:
    MenuObjectMap();
    void loadObjectLayer(const tmx::ObjectGroup& layer) override;
    MenuComponent getPlayerMenuComponent();

private:
    Logger logger;
    MenuComponent playerMenu;
    void loadPlayerMenu(const std::vector<tmx::Object> &objects);
};


#endif //NEWNEW_MENUOBJECTMAP_H
