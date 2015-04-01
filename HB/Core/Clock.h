#ifndef HB_CLOCK_H
#define HB_CLOCK_H
#include <chrono>
#include "Time.h"

namespace hb
{
	class Clock
	{
	public:
		/*!
		  \brief Class constructor.

		  Initializes a new instance of Clock wich starts measuring 
		  the time as it is created.
		*/
		Clock();
		/*!
		  \brief Class destructor.

		  Destroys the instance of Clock.
		*/
		~Clock();
		/*!
		  \brief Returns the Time elapsed since creation or last reset.

		  \return Time since instance creation or last reset().
		*/
		Time getElapsedTime() const;
		/*!
		  \brief Restarts the Time counter.
		  
		  This function also returns the time elapsed up to its reset.
		  This is usefull for getting precise delta times without having 
		  time overhead for having to call two methods:
		  \code
		  hb::Clock clk;
		  while(game_is_running)
		  {
		      hb::Time deltaTime = clk.reset();
		      ... // Game code
		  }
		  \endcode

		  \return Time since instance creation or last reset().
		*/
		Time reset();
		
	private:
		std::chrono::high_resolution_clock::time_point m_time_point;
	};
}
#endif

/**
 * \class hb::Clock
 * \ingroup core
 * \brief A class for measuring Time intervals.
 */
