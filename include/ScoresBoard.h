#pragma once 
#include <string>
#include <map>
#include <fstream>
#include "Resources.h"
#include <istream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "MenuButton.h"

const int NUM_OF_RECORDS = 10;

class ScoresBoard {

public:

	ScoresBoard();
	void createBackGround();
	void draw(sf::RenderWindow& window, const std::multimap <int, std::string>& records);
	void drawScore(const std::multimap <int, std::string>& records, sf::RenderWindow& window);
	void handleEvent(sf::RenderWindow& window);
	void handleClick();
	int whoPreesed();
private:
	std::vector<std::unique_ptr< Button>> m_buttons;
	sf::Sprite m_bg;
	Animation m_bgAnimation;

	bool m_isScoresOpen = true;
};