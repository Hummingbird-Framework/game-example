#include "TmxObjectTypeFactory.h"
using namespace hb;

std::unordered_map<std::string, lambdaFactory> TmxObjectTypeFactory::s_factory_table;

TmxObjectTypeFactory::TmxObjectTypeFactory()
{

}


TmxObjectTypeFactory::~TmxObjectTypeFactory()
{

}


void TmxObjectTypeFactory::registerFactory(const std::string& type, lambdaFactory&& factory)
{
	s_factory_table[type] = std::move(factory);
}


void TmxObjectTypeFactory::registerFactory(const std::string& type, GameObjectFactory factory)
{
	s_factory_table[type] = factory;
}


void TmxObjectTypeFactory::makeObject(const Tmx::Map* map, int obj_grp, int obj)
{
	HB_CHECK_TMXPARSER_VERSION();
	const Tmx::Object* object = map->GetObjectGroup(obj_grp)->GetObject(obj);
	if (object->GetType() == "")
		return;

	auto it = s_factory_table.find(object->GetType());
	if (it == s_factory_table.end())
	{
		hb_log_d("TmxObjectTypeFactory: Type `" << object->GetType() << "` not registered, skipping object.");
		return;
	}
	GameObject* go = new GameObject(object->GetId());
	go->setName(object->GetType());
	hb::Vector3d v = hb::Renderer::getCamera().DrawspaceToObjectspace(hb::Vector3d(object->GetX(), object->GetY(), map->GetObjectGroup(obj_grp)->GetZOrder()));
	go->setPosition(v);
	it->second(go, map, obj_grp, obj);
}
