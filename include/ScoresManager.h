#pragma once

#include <string>
#include <map>
#include <fstream>
#include "Resources.h"
#include <istream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>

class ScoresManager {

public:
	ScoresManager();
	void readRecords();

	void writeRecords();
	bool isRecord(int);
	const std::multimap<int, std::string, std::greater<int>>& getRecords() const;

	void addRecord(sf::RenderWindow&, const int, const std::string&);

private:

	std::multimap <int, std::string, std::greater<int>> m_records;
	std::vector<sf::Sprite> m_sprites;
	std::vector<sf::Text> m_text;
};
