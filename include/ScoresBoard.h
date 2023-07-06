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

enum ButtonIndexScore
{
	MENU_BUTTON,
	MAX_S
};


class ScoresBoard 
{

public:
	void run();
	ScoresBoard(sf::RenderWindow&, const std::multimap <int, std::string, std::greater<int>>&);
	void createBackGround();
	void draw();
	void drawScore();
	void handleEvent(sf::RenderWindow& window);
	void handleClick();
	ButtonIndexScore getPressedButton();
private:

	void mouseMovedEvent(const sf::Event& event);
	void mouseReleasedEvent(const sf::Event& event);

	std::vector<std::unique_ptr< Button>> m_buttons;
	sf::Sprite m_bg;
	Animation m_bgAnimation;

	sf::RenderWindow& m_window;
	const std::multimap <int, std::string, std::greater<int>>& m_recordList;

	bool m_isScoresOpen = true;
};