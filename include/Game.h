#pragma once

#include "SFML/Graphics.hpp"
#include "Level.h"

class Game
{
public:

	Game(sf::RenderWindow& window);

	void run();


private:

	sf::RenderWindow& m_window;

};