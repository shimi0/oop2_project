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
	void addObject(std::string type, sf::Vector2f pos)
	{
		m_simplePlatformsVec.push_back(Factory::instance().create(type, m_world, m_bodyDef, pos));
	}
	

private:

	void adjustView(sf::View&);
	void processEvent(const sf::Time&);
	void drawGraphics();

	sf::RenderWindow& m_window;
	Board m_board;
	//SimplePlatform m_platform;		//temp
	Player m_player;
	std::unique_ptr<b2World> m_world;
	b2BodyDef m_bodyDef;
	std::vector<std::unique_ptr<GameObject>> m_simplePlatformsVec;	//uniqe_ptr???

};