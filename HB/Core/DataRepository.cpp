#include "DataRepository.h"
using namespace hb;


DataRepository::DataRepository():
m_data()
{
}


DataRepository::~DataRepository()
{

}


void DataRepository::setInt(const std::string& name, int value)
{
	m_data[name].i = value;
}


int DataRepository::getInt(const std::string& name, int default_value)
{
	auto it = m_data.find(name);
	if (it != m_data.end())
		return it->second.i;
	return default_value;
}


void DataRepository::setUInt(const std::string& name, unsigned int value)
{
	m_data[name].ui = value;
}


int DataRepository::getUInt(const std::string& name, unsigned int default_value)
{
	auto it = m_data.find(name);
	if (it != m_data.end())
		return it->second.ui;
	return default_value;
}


void DataRepository::setDouble(const std::string& name, double value)
{
	m_data[name].d = value;
}


double DataRepository::getDouble(const std::string& name, double default_value)
{
	auto it = m_data.find(name);
	if (it != m_data.end())
		return it->second.d;
	return default_value;
}


void DataRepository::setFloat(const std::string& name, float value)
{
	m_data[name].f = value;
}


float DataRepository::getFloat(const std::string& name, float default_value)
{
	auto it = m_data.find(name);
	if (it != m_data.end())
		return it->second.f;
	return default_value;
}


void DataRepository::setChar(const std::string& name, char value)
{
	m_data[name].c = value;
}


char DataRepository::getChar(const std::string& name, char default_value)
{
	auto it = m_data.find(name);
	if (it != m_data.end())
		return it->second.c;
	return default_value;
}


void DataRepository::setBool(const std::string& name, bool value)
{
	m_data[name].b = value;
}


bool DataRepository::getBool(const std::string& name, bool default_value)
{
	auto it = m_data.find(name);
	if (it != m_data.end())
		return it->second.b;
	return default_value;
}


void DataRepository::setPointer(const std::string& name, void* value)
{
	m_data[name].p = value;
}
