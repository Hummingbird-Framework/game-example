#include "Time.h"
using namespace hb;

Time Time::deltaTime = Time::microseconds(0);

Time::Time():
m_microseconds(0)
{

}


Time::~Time()
{}


double Time::asSeconds() const
{
	return (double)m_microseconds/1e6;
}


int Time::asMilliseconds() const
{
	return m_microseconds/1000;
}


long long Time::asMicroseconds() const
{
	return m_microseconds;
}


Time Time::seconds(double seconds)
{
	Time t;
	t.m_microseconds = (long long)(seconds * 1e6);
	return t;
}


Time Time::milliseconds(int milliseconds)
{
	Time t;
	t.m_microseconds = milliseconds * 1000;
	return t;
}


Time Time::microseconds(long long microseconds)
{
	Time t;
	t.m_microseconds = microseconds;
	return t;
}


bool operator ==(hb::Time left, hb::Time right)
{
	return left.asMicroseconds() == right.asMicroseconds();
}


bool operator !=(hb::Time left, hb::Time right)
{
	return left.asMicroseconds() != right.asMicroseconds();
}


bool operator <(hb::Time left, hb::Time right)
{
	return left.asMicroseconds() < right.asMicroseconds();
}


bool operator >(hb::Time left, hb::Time right)
{
	return left.asMicroseconds() > right.asMicroseconds();
}


bool operator <=(hb::Time left, hb::Time right)
{
	return left.asMicroseconds() <= right.asMicroseconds();
}


bool operator >=(hb::Time left, hb::Time right)
{
	return left.asMicroseconds() >= right.asMicroseconds();
}


hb::Time operator -(hb::Time right)
{
	return Time::microseconds(-right.asMicroseconds());
}


hb::Time operator +(hb::Time left, hb::Time right)
{
	return Time::microseconds(left.asMicroseconds() + right.asMicroseconds());
}


hb::Time & operator +=(hb::Time &left, hb::Time right)
{
	left = left + right;
	return left;
}


hb::Time operator -(hb::Time left, hb::Time right)
{
	return Time::microseconds(left.asMicroseconds() - right.asMicroseconds());
}


hb::Time & operator -=(hb::Time &left, hb::Time right)
{
	left = left - right;
	return left;
}


hb::Time operator *(hb::Time left, double right)
{
	return Time::microseconds(left.asMicroseconds() * right);
}


hb::Time operator *(hb::Time left, long long right)
{
	return Time::microseconds(left.asMicroseconds() * right);
}


hb::Time operator *(double left, hb::Time right)
{
	return Time::microseconds(left * right.asMicroseconds());
}


hb::Time operator *(long long left, hb::Time right)
{
	return Time::microseconds(left * right.asMicroseconds());
}


hb::Time & operator *=(hb::Time &left, double right)
{
	left = left * right;
	return left;
}


hb::Time & operator *=(hb::Time &left, long long right)
{
	left = left * right;
	return left;
}


hb::Time operator /(hb::Time left, double right)
{
	return Time::microseconds(left.asMicroseconds() / right);
}


hb::Time operator /(hb::Time left, long long right)
{
	return Time::microseconds(left.asMicroseconds() / right);
}


hb::Time & operator /=(hb::Time &left, double right)
{
	left = left / right;
	return left;
}


hb::Time & operator /=(hb::Time &left, long long right)
{
	left = left / right;
	return left;
}


double operator /(hb::Time left, hb::Time right)
{
	return (double)left.asMicroseconds() / (double)right.asMicroseconds();
}


hb::Time operator %(hb::Time left, hb::Time right)
{
	return Time::microseconds(left.asMicroseconds() % right.asMicroseconds());
}


hb::Time & operator %=(hb::Time &left, hb::Time right)
{
	left = left % right;
	return left;
}
