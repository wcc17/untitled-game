#ifndef NEWNEW_MENUMAP_H
#define NEWNEW_MENUMAP_H


#include "Map.h"
#include "MenuObjectMap.h"
#include "../ui/component/MenuLayer.h"

class MenuMap : public Map {

public:
    void loadObjectLayer(const tmx::ObjectGroup& layer) override;
    MenuObjectMap getMenuObjectMap();
    MenuLayer getPlayerMenuLayer();
    void setPlayerMenuLayer(MenuLayer playerMenuLayer);

private:
    MenuObjectMap menuObjectMap;
    MenuLayer playerMenuLayer;
};


#endif //NEWNEW_MENUMAP_H
