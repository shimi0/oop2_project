#pragma once

#include "SFML/Graphics.hpp"
#include "Level.h"
#include "DataReader.h"
#include <fstream>
#include "Factory.h"
#include "GameOver.h"

class Game
{
public:

	Game(sf::RenderWindow& window);

	void run();


private:

	void readGameData(Level& level);

	sf::RenderWindow& m_window;

	Board m_board;

};