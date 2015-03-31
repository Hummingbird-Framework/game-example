#ifndef HB_OBJECT_TYPE_FACTORY
#define HB_OBJECT_TYPE_FACTORY
#include <cstdlib>
#include <functional>
#include <string>
#include <unordered_map>
#include <map>
#include <tmxparser/Tmx.h>
#include "../Core/GameObject.h"
#include "../SFML/ClickableComponent.h"
#include "TmxVersion.h"

namespace hb
{
	/**
	 * \addtogroup tmx
	 * @{
	 */
	typedef void(*GameObjectFactory)(GameObject*, const Tmx::Map*, int, int);
	typedef std::function<void(GameObject*, const Tmx::Map*, int, int)> lambdaFactory;
	class TmxObjectTypeFactory
	{
	public:
		TmxObjectTypeFactory();
		~TmxObjectTypeFactory();
		static void registerFactory(const std::string& type, lambdaFactory&& factory);
		static void registerFactory(const std::string& type, GameObjectFactory factory);
		static void makeObject(const Tmx::Map* map, int obj_grp, int obj);

	private:
		static std::unordered_map<std::string, lambdaFactory> s_factory_table;
	};

	inline void TmxRegisterFactory(const std::string& type, GameObjectFactory factory)
	{
		TmxObjectTypeFactory::registerFactory(type, factory);
	}

	inline void TmxRegisterFactory(const std::string& type, lambdaFactory&& factory)
	{
		TmxObjectTypeFactory::registerFactory(type, std::move(factory));
	}
	//! @}
}
#endif