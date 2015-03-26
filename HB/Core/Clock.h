#ifndef HB_CLOCK_H
#define HB_CLOCK_H
#include <chrono>
#include "Time.h"

namespace hb
{
	//! A class for measuring time intervals
	class Clock
	{
	public:
		//! Class constructor
		/*!
		  Initializes a new instance of Clock wich starts measuring 
		  the time since it is created.
		*/
		Clock();
		//! Class destructor
		~Clock();
		//! Returns the Time elapsed since creation or last reset
		Time getElapsedTime() const;
		//! Returns the Time elapsed since creation or last reset and resets the counter
		Time reset();
		
	private:
		std::chrono::high_resolution_clock::time_point m_time_point;
	};
}
#endif
