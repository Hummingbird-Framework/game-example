#ifndef HB_EVENT_MANAGER_H
#define HB_EVENT_MANAGER_H
#include <functional>
#include <vector>

namespace hb
{
	namespace detail
	{
		template <typename Event>
		class EventManager
		{
		public:
			typedef std::function<void(const Event&)> Listener;
			int listen(Listener&& listener)
			{
				m_listeners.push_back(std::move(listener));
				m_is_active.push_back(true);
				return m_listeners.size()-1;
			}

			void message(const Event& event)
			{
				for (unsigned int i = 0; i < m_listeners.size(); ++i)
				{
					if (m_is_active[i])
						m_listeners[i](event);
				}
			}

			void ignore(int id)
			{
				m_is_active[id] = false;
				m_disabled.push_back(id);
			}

		private:
			std::vector<Listener> m_listeners;
			std::vector<int> m_disabled;
			std::vector<bool> m_is_active;
		};

		template <typename T>
		struct traits : public traits<decltype(&T::operator())> {};

		template <typename C, typename R, typename A>
		struct traits<R(C::*)(const A&) const>
		{
			typedef A type;
		};
	}

	template <typename... Events>
	class EventManager : detail::EventManager<Events>...
	{
	public:
		template <typename Event>
		struct ListenerId
		{
			typedef Event type;
			int id;
		};

		template <typename Listener>
		ListenerId<typename detail::traits<Listener>::type> listen(Listener&& listener)
		{
			typedef typename detail::traits<Listener>::type Event;
			detail::EventManager<Event>& em = *this;
			ListenerId<Event> ret;
			ret.id = em.listen(std::move(listener));
			return ret;
		}

		template <typename Event>
		void message(const Event& event)
		{
			detail::EventManager<Event>& em = *this;
			em.message(event);
		}

		template <typename Event>
		void ignore(const ListenerId<Event>& id)
		{
			detail::EventManager<Event>& em = *this;
			em.ignore(id.id);
		}
	};
}
#endif