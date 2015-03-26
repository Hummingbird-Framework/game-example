#include "HB/Core.h"
#include "HB/SFML.h"
#include "HB/Tmx.h"
#include "SwitchComponent.h"

// Define Object factories
void makePlayer(const Tmx::Map* map, int obj_grp, int obj_id);
void makeWall(const Tmx::Map* map, int obj_grp, int obj_id);
void makeSwitch(const Tmx::Map* map, int obj_grp, int obj_id);
void makeBridge(const Tmx::Map* map, int obj_grp, int obj_id);
void makeDoor(const Tmx::Map* map, int obj_grp, int obj_id);
