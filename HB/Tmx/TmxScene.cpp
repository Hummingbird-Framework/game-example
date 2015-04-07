#include "TmxScene.h"
using namespace hb;


TmxScene::TmxScene(const std::string& scene_name, const std::string& file_name, std::function<void(const Tmx::Map*)>&& post_init):
Game::Scene(scene_name, [](){}),
m_post_init(std::move(post_init))
{
	HB_CHECK_TMXPARSER_VERSION();
	m_init = [this, file_name]()
	{
		Tmx::Map* map = new Tmx::Map();
		map->ParseFile(file_name);
		if (map->HasError())
		{
			hb_log("error code: " << map->GetErrorCode() << std::endl);
			hb_log("error text: " << map->GetErrorText().c_str() << std::endl);

			std::exit(map->GetErrorCode());
		}

		int last_slash = file_name.find_last_of("/");
		std::string path = file_name.substr(0, last_slash +1);

		std::string c = map->GetBackgroundColor();
		if (c.size() != 0)
		{
			int r = std::stoul(c.substr(1,2), nullptr, 16);
			int g = std::stoul(c.substr(3,2), nullptr, 16);
			int b = std::stoul(c.substr(5,2), nullptr, 16);
			Color color(r, g, b);
			Renderer::setClearColor(color);
		}

		if (map->GetOrientation() == Tmx::TMX_MO_ORTHOGONAL)
		{
			Renderer::getCamera().setAxisX(Vector3d(map->GetTileWidth(), 0, 0));
			Renderer::getCamera().setAxisY(Vector3d(0, map->GetTileHeight(), 0));
			Renderer::getCamera().setAxisZ(Vector3d(0, 0, 1));
		}
		else if (map->GetOrientation() == Tmx::TMX_MO_ISOMETRIC)
		{
			Renderer::getCamera().setAxisX(Vector3d(map->GetTileWidth(), map->GetTileHeight(), map->GetTileHeight()));
			Renderer::getCamera().setAxisY(Vector3d(-map->GetTileWidth(), map->GetTileHeight(), map->GetTileHeight()));
			Renderer::getCamera().setAxisZ(Vector3d(0, 0, 1));
		}

		GameObject::setNextGameObjectId(map->GetNextObjectId());

		// Make Image layers
		for (int i = 0; i < map->GetNumImageLayers(); ++i)
		{
			const Tmx::ImageLayer* layer = map->GetImageLayer(i);
			if (not layer->IsVisible()) continue;

			GameObject *image_layer_go = new GameObject();
			image_layer_go->setName(layer->GetName());
			image_layer_go->setPosition(Vector3d(layer->GetX()/map->GetTileWidth(), layer->GetY()/map->GetTileHeight(), layer->GetZOrder()));

			Texture tex = Texture::loadFromFile(path + layer->GetImage()->GetSource(), Rect(0, 0, layer->GetImage()->GetWidth(), layer->GetImage()->GetHeight()));
			Sprite sprite = Sprite(tex);
			auto sprite_comp = new SpriteComponent(sprite);
			image_layer_go->addComponent(sprite_comp);
		}

		// Make tile layers
		for (int i = 0; i < map->GetNumTileLayers(); ++i)
		{
			const Tmx::TileLayer* layer = map->GetTileLayer(i);
			if (not layer->IsVisible()) continue;

			GameObject *tile_layer_go = new GameObject();
			tile_layer_go->setName(layer->GetName());
			tile_layer_go->setPosition(Vector3d(0, 0, layer->GetZOrder()));
			for (int y = 0; y < layer->GetHeight(); ++y)
			{
				for (int x = 0; x < layer->GetWidth(); ++x)
				{
					if (layer->GetTileTilesetIndex(x, y) == -1) continue;
					int gid = layer->GetTileGid(x, y);
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
					auto sprite_comp = new SpriteComponent(sprite, anim, t_anim);
					sprite_comp->setPosition(Vector3d(x, y, 0));
					tile_layer_go->addComponent(sprite_comp);
				}
			}
		}

		// Make GameObjects
		for (int i = 0; i < map->GetNumObjectGroups(); ++i)
		{
			const Tmx::ObjectGroup* obj_grp = map->GetObjectGroup(i);
			if (not obj_grp->IsVisible()) continue;
			for (int j = 0; j < obj_grp->GetNumObjects(); ++j)
			{
				TmxObjectTypeFactory::makeObject(map, i, j);
			}
		}
		
		m_post_init(map);

		delete map;
	};
}


TmxScene::TmxScene(const std::string& scene_name, const std::string& file_name, std::function<void(const Tmx::Map*)>& post_init):
TmxScene(scene_name, file_name, std::function<void(const Tmx::Map*)>(post_init))
{

}


TmxScene::~TmxScene()
{

}
