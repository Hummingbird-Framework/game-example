#ifndef HB_TIME_H
#define HB_TIME_H

namespace hb
{
	/*!
	  \class Time
	  \ingroup core
	  \brief Class for representing intervals of time.

	  This class has microseconds precision.
	*/
	class Time
	{
	public:
		/*!
		  \brief Default constructor.
		*/
		Time();
		/*!
		  \brief Class destructor.
		*/
		~Time();
		/*!
		  \brief Get Time as seconds.
		  \return Number of seconds represented.
		*/
		double asSeconds() const;
		/*!
		  \brief Get Time as milliseconds.
		  \return Number of milliseconds represented.
		*/
		int asMilliseconds() const;
		/*!
		  \brief Get Time as microseconds.
		  \return Number of microseconds represented.
		*/
		long long asMicroseconds() const;

		/*!
		  \brief Construct Time from seconds.
		*/
		static Time seconds(double seconds);
		/*!
		  \brief Construct Time from milliseconds.
		*/
		static Time milliseconds(int milliseconds);
		/*!
		  \brief Construct Time from microseconds.
		*/
		static Time microseconds(long long microseconds);
		//! Game delta Time.
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