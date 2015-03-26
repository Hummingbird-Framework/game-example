#ifndef HB_TIME_H
#define HB_TIME_H

namespace hb
{
	/*!
	  \class Time
	  \ingroup core
	*/
	class Time
	{
	public:
		Time();
		~Time();
		double asSeconds() const;
		int asMilliseconds() const;
		long long asMicroseconds() const;

		static Time seconds(double seconds);
		static Time milliseconds(int milliseconds);
		static Time microseconds(long long microseconds);
		static Time deltaTime;
		
	private:
		long long m_microseconds;
	};
}

bool operator ==(hb::Time left, hb::Time right);
bool operator !=(hb::Time left, hb::Time right);
bool operator <(hb::Time left, hb::Time right);
bool operator >(hb::Time left, hb::Time right);
bool operator <=(hb::Time left, hb::Time right);
bool operator >=(hb::Time left, hb::Time right);
hb::Time operator -(hb::Time right);
hb::Time operator +(hb::Time left, hb::Time right);
hb::Time& operator +=(hb::Time &left, hb::Time right);
hb::Time operator -(hb::Time left, hb::Time right);
hb::Time& operator -=(hb::Time &left, hb::Time right);
hb::Time operator *(hb::Time left, double right);
hb::Time operator *(hb::Time left, long long right);
hb::Time operator *(double left, hb::Time right);
hb::Time operator *(long long left, hb::Time right);
hb::Time& operator *=(hb::Time &left, double right);
hb::Time& operator *=(hb::Time &left, long long right);
hb::Time operator /(hb::Time left, double right);
hb::Time operator /(hb::Time left, long long right);
hb::Time& operator /=(hb::Time &left, double right);
hb::Time& operator /=(hb::Time &left, long long right);
double operator /(hb::Time left, hb::Time right);
hb::Time operator %(hb::Time left, hb::Time right);
hb::Time& operator %=(hb::Time &left, hb::Time right);
#endif