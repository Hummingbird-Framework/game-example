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
	const Tmx::Object* object = map->GetObjectGroup(obj_grp)->GetObject(obj);
	if (object->GetType() == "")
		return;

	auto it = s_factory_table.find(object->GetType());
	if (it == s_factory_table.end())
	{
		printf("TmxObjectTypeFactory: Type %s not registered, skipping object.\n", object->GetType().c_str());
		return;
	}
	it->second(map, obj_grp, obj);
}
