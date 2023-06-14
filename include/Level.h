#pragma once

#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Player.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "SimplePlatform.h"
#include "ContactListener.h"
#include <vector>

class Level
{
public:

	Level(sf::RenderWindow& window);

	void run();
	

private:

	void processEvent(const sf::Time&);
	void drawGraphics();

	sf::RenderWindow& m_window;
	Board m_board;
	//SimplePlatform m_platform;		//temp
	Player m_player;

	std::vector<SimplePlatform> m_simplePlatformsVec;	//uniqe_ptr???

};