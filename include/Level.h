#pragma once

#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Player.h"
#include "macros.h"
#include "box2d/box2d.h"

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