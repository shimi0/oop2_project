#include "DataReader.h"

DataReader::DataReader(const std::string& filePath) 
	:m_filePath(filePath)
{}

//-------------------------------------------------

void DataReader::openFile()
{
	m_file.open(m_filePath);
	if (!m_file)
		throw std::runtime_error("Failed to open file: " + m_filePath);
}

//-------------------------------------------------

Object DataReader::readObject()
{
	auto x = std::string();
	auto y = std::string();
	Object object;
	if (!(m_file >> object.type >> x >> y))
	{
		throw std::runtime_error("Failed to read");
	}

	object.position.x = std::stof(x);
	object.position.y = std::stof(y);

	return object;
}

//------------------------------------------------

