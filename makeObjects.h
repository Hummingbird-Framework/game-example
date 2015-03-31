#include "HB/Core.h"
#include "HB/SFML.h"
#include "HB/Tmx.h"
#include "SwitchComponent.h"

// Define Object factories
void makePlayer(hb::GameObject* go, const Tmx::Map* map, int obj_grp, int obj_id);
void makeWall(hb::GameObject* go, const Tmx::Map* map, int obj_grp, int obj_id);
void makeSwitch(hb::GameObject* go, const Tmx::Map* map, int obj_grp, int obj_id);
void makeBridge(hb::GameObject* go, const Tmx::Map* map, int obj_grp, int obj_id);
void makeDoor(hb::GameObject* go, const Tmx::Map* map, int obj_grp, int obj_id);
