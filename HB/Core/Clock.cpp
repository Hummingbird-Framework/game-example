#include "Clock.h"
using namespace hb;
Clock::Clock()
{
	m_time_point = std::chrono::high_resolution_clock::now();
}


Clock::~Clock()
{}


Time Clock::getElapsedTime() const
{
	auto elapsed = std::chrono::high_resolution_clock::now() - m_time_point;
	return Time::microseconds(std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count());
}


Time Clock::reset()
{
	Time t = getElapsedTime();
	m_time_point = std::chrono::high_resolution_clock::now();
	return t;
}