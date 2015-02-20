#ifndef HB_CLOCK_H
#define HB_CLOCK_H
#include <chrono>
#include "Time.h"

namespace hb
{
	class Clock
	{
	public:
		Clock();
		~Clock();
		Time getElapsedTime() const;
		Time reset();
		
	private:
		std::chrono::high_resolution_clock::time_point m_time_point;
	};
}
#endif