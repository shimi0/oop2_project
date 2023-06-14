#pragma once

#include "SFML/Graphics.hpp"
#include "Level.h"
#include "DataReader.h"

class Game
{
public:

	Game(sf::RenderWindow& window);

	void run();


private:

	sf::RenderWindow& m_window;
	DataReader m_dataReader;

};