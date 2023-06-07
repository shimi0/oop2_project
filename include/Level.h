#pragma once

#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Player.h"

class Level
{
public:

	Level(sf::RenderWindow& window);

	void run();


private:

	sf::RenderWindow& m_window;
	Board m_board;
	Player m_player;
};