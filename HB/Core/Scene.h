#ifndef HB_SCENE_H
#define HB_SCENE_H
#include <string>
#include <functional>

namespace hb
{
	class Scene
	{
	public:
		Scene(const std::string& name, std::function<void(void)>&& init);
		Scene(const Scene& other);
		Scene(Scene&& other);
		~Scene();

		void init();
		void exit();
		const std::string& getName() const;
		void setExit(std::function<void(void)>&& exit);

	private:
		std::function<void(void)> m_init, m_exit;
		std::string m_name;
	};
}
#endif