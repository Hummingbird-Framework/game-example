#ifndef HB_DATA_REPOSITORY_H
#define HB_DATA_REPOSITORY_H
#include <string>
#include <unordered_map>

namespace hb
{
	/*!
	  \class DataRepository
	  \ingroup core
	*/
	class DataRepository
	{
	public:
		DataRepository();
		~DataRepository();

		void setInt(const std::string& name, int value);
		int getInt(const std::string& name, int default_value = -1);
		void setUInt(const std::string& name, unsigned int value);
		int getUInt(const std::string& name, unsigned int default_value = 0);
		void setDouble(const std::string& name, double value);
		double getDouble(const std::string& name, double default_value = -1.);
		void setFloat(const std::string& name, float value);
		float getFloat(const std::string& name, float default_value = -1.f);
		void setChar(const std::string& name, char value);
		char getChar(const std::string& name, char default_value = 0x00);
		void setBool(const std::string& name, bool value);
		bool getBool(const std::string& name, bool default_value = false);
		void setPointer(const std::string& name, void* value);
		template <typename T>
		T* getPointer(const std::string& name, T* default_value = nullptr)
		{
			auto it = m_data.find(name);
			if (it != m_data.end())
				return static_cast<T*>(m_data[name].p);
			return default_value;
		}

	private:
		union Data
		{
			int i;
			unsigned int ui;
			double d;
			float f;
			char c;
			bool b;
			void* p;
		};
		std::unordered_map<std::string, Data> m_data;
	};
}
#endif