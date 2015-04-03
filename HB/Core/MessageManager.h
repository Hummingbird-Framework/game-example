#ifndef HB_EVENT_MANAGER_H
#define HB_EVENT_MANAGER_H
#include <algorithm>
#include <functional>
#include <string>
#include <map>
#include <vector>

namespace hb
{
	namespace detail
	{
		template <typename Type>
		class MessageManager
		{
		public:
			typedef std::function<void(Type&)> Listener;
			typedef typename std::multimap<std::string, Listener> function_map;
			typedef typename function_map::iterator map_iterator;

			map_iterator listen(Listener&& listener)
			{
				return m_listeners.insert(std::pair<std::string, Listener>("", std::move(listener)));
			}

			map_iterator listen(const std::string& name, Listener&& listener)
			{
				return m_listeners.insert(std::pair<std::string, Listener>(name, std::move(listener)));
			}

			void message(Type& event)
			{
				std::for_each(m_listeners.begin(), m_listeners.end(),
					[&event](typename function_map::value_type& x)
					{
						x.second(event);
					});
			}

			void message(const std::string& name, Type& event)
			{
				auto range = m_listeners.equal_range("");
				std::for_each(range.first, range.second,
					[&event](typename function_map::value_type& x)
					{
						x.second(event);
					});

				if (name == "") return;

				range = m_listeners.equal_range(name);
				std::for_each(range.first, range.second,
					[&event](typename function_map::value_type& x)
					{
						x.second(event);
					});
			}

			void ignore(map_iterator it)
			{
				m_listeners.erase(it);
			}

		private:
			function_map m_listeners;
		};

		template <typename T>
		struct traits : public traits<decltype(&T::operator())> {};

		template <typename C, typename R, typename A>
		struct traits<R(C::*)(A&) const>
		{
			typedef A type;
		};
	}

	/*!
	  \class MessageManager
	  \brief Generic message manager class.
	  \ingroup core

	  This class allows to define callbacks for a set of predefined events with name filter.
	  Callbacks listening to messages with empty name ("") will be called always.
	*/
	template <typename... Types>
	class MessageManager : detail::MessageManager<Types>...
	{
	public:
		/*!
		  \struct ListenerId
		  \brief Identifier of a registered listener.

		  This is used for disabling a listener.
		*/
		template <typename Type>
		struct ListenerId
		{
			typedef Type type;
			typename std::multimap<std::string, std::function<void(Type&)>>::iterator it;
		};

		/*!
		  \brief Connects a listener to all messages of a type (no name filtering).
		  \param listener Listener function for the message.
		  \return Identifier used for disabling this listener.
		*/
		template <typename Listener>
		ListenerId<typename detail::traits<Listener>::type> listen(Listener&& listener)
		{
			typedef typename detail::traits<Listener>::type Type;
			detail::MessageManager<Type>& em = *this;
			ListenerId<Type> ret;
			ret.it = em.listen(std::move(listener));
			return ret;
		}

		/*!
		  \brief Connects a listener to all messages of a type with name _name_.
		  \param listener Callback function for the message.
		  \return Identifier used for disabling this listener.
		*/
		template <typename Listener>
		ListenerId<typename detail::traits<Listener>::type> listen(const std::string& name, Listener&& listener)
		{
			typedef typename detail::traits<Listener>::type Type;
			detail::MessageManager<Type>& em = *this;
			ListenerId<Type> ret;
			ret.it = em.listen(name, std::move(listener));
			return ret;
		}

		/*!
		  \brief Send a message to all listeners of a type (no name filtering)
		  \param event Type of the message being sent
		*/
		template <typename Type>
		void message(Type& event)
		{
			detail::MessageManager<Type>& em = *this;
			em.message(event);
		}

		/*!
		  \brief Send a message to all listeners of a type with name _name_
		  \param event Type of the message being sent
		*/
		template <typename Type>
		void message(const std::string& name, Type& event)
		{
			detail::MessageManager<Type>& em = *this;
			em.message(name, event);
		}

		/*!
		  \brief Disable the listener identified by id
		  \param id Id returned by listen() when the listener was registered
		*/
		template <typename Type>
		void ignore(const ListenerId<Type>& id)
		{
			detail::MessageManager<Type>& em = *this;
			em.ignore(id.it);
		}
	};
}
#endif