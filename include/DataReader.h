#pragma once
#include <string>
#include <fstream>
#include "SFML/Graphics.hpp"

struct Object
{
	std::string type;
	sf::Vector2f position;
};

class DataReader
{
public:
	DataReader(const std::string& filePath);

	void openFile();
	struct Object readObject();
	bool isEOF() const
	{
		return m_file.eof();
	}

private:

	std::string m_filePath;
	std::fstream m_file;

};
