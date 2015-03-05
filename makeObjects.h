#include "HB/Base.h"
#include "HB/SFML.h"

hb::GameObject* makePlayer(hb::RenderWindowManager* window_manager1);
hb::GameObject* makeWall(hb::RenderWindowManager* window_manager, const hb::Vector2d& position, const hb::Vector2d& size);
hb::GameObject* makeBullet(hb::RenderWindowManager* window_manager, const hb::Vector2d& direction);