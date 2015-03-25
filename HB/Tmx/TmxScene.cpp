#include "TmxScene.h"
using namespace hb;


TmxScene::TmxScene(const std::string& scene_name, const std::string& file_name):
Game::Scene(scene_name, [](){}),
m_filename(file_name)
{
	m_init = [this]()
	{
		Tmx::Map* map = new Tmx::Map();
		map->ParseFile(m_filename);
		if (map->HasError())
		{
			printf("error code: %d\n", map->GetErrorCode());
			printf("error text: %s\n", map->GetErrorText().c_str());

			system("PAUSE");

			::exit(map->GetErrorCode());
		}
		int last_slash = m_filename.find_last_of("/");
		std::string path = m_filename.substr(0, last_slash +1);

		Renderer::getWindow().setSize(sf::Vector2u(map->GetWidth() * map->GetTileWidth(), map->GetHeight() * map->GetTileHeight()));
		Renderer::getCamera().setPosition(Vector2d(map->GetWidth()/4., map->GetHeight()/4.));
		Renderer::getWindow().setView(sf::View(sf::FloatRect(0, 0, map->GetWidth() * map->GetTileWidth(), map->GetHeight() * map->GetTileHeight())));

		if (map->GetOrientation() == Tmx::TMX_MO_ORTHOGONAL)
		{
			Renderer::getCamera().setAxisX(Vector3d(map->GetTileWidth(), 0, 0));
			Renderer::getCamera().setAxisY(Vector3d(0, map->GetTileHeight(), 0));
			Renderer::getCamera().setAxisZ(Vector3d(0, 0, 1));
		}
		else if (map->GetOrientation() == Tmx::TMX_MO_ISOMETRIC)
		{
			Renderer::getCamera().setAxisX(Vector3d(map->GetTileWidth(), map->GetTileHeight()/2., map->GetTileHeight()/2.));
			Renderer::getCamera().setAxisY(Vector3d(-map->GetTileWidth(), map->GetTileHeight()/2., map->GetTileHeight()/2.));
			Renderer::getCamera().setAxisZ(Vector3d(0, 0, 1));
		}

		for (int i = 0; i < map->GetNumTileLayers(); ++i)
		{
			const Tmx::TileLayer* layer = map->GetTileLayer(i);
			if (not layer->IsVisible()) continue;
			for (int y = 0; y < layer->GetHeight(); ++y)
			{
				for (int x = 0; x < layer->GetWidth(); ++x)
				{
					if (layer->GetTileTilesetIndex(x, y) == -1) continue;
					int gid = layer->GetTileId(x, y);
					const Tmx::Tileset *tileset = map->FindTileset(gid);
					int lid = gid - tileset->GetFirstGid();
					std::vector<int> anim;
					Time t_anim = Time::seconds(0);
					const Tmx::Tile* tile = tileset->GetTile(lid);
					if (tile->IsAnimated())
					{
						t_anim = Time::milliseconds(tile->GetTotalDuration() / tile->GetFrameCount());
						for (auto anim_frame : tile->GetFrames())
						{
							anim.push_back(anim_frame.GetTileID());
						}
					}
					else
					{
						anim.push_back(lid);
					}
					Texture tex = Texture::loadFromFile(path + tileset->GetImage()->GetSource(), Rect(0, 0, tileset->GetImage()->GetWidth(), tileset->GetImage()->GetHeight()));
					Sprite sprite = Sprite(tex, Vector2d(tileset->GetTileWidth(), tileset->GetTileHeight()), Vector2d(tileset->GetMargin(), tileset->GetMargin()));
					GameObject* tile_obj = new GameObject(
						{
							new SpriteComponent(sprite, anim, t_anim)
						});
					tile_obj->setPosition(Vector3d(x, y, layer->GetZOrder()));
				}
			}
		}

		for (int i = 0; i < map->GetNumObjectGroups(); ++i)
		{
			const Tmx::ObjectGroup* obj_grp = map->GetObjectGroup(i);
			for (int j = 0; j < obj_grp->GetNumObjects(); ++j)
			{
				TmxObjectTypeFactory::makeObject(map, i, j);
			}
		}
		

		delete map;
	};

}


TmxScene::~TmxScene()
{

}
