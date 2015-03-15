#include "HB/Core.h"
#include "HB/SFML.h"

hb::GameObject* makePlayer();
hb::GameObject* makeWall(const hb::Vector2d& position, const hb::Vector2d& size);
hb::GameObject* makeBullet(const hb::Vector2d& direction);