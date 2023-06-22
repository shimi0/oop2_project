#pragma once

#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Player.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "StaticPlatform.h"
#include "ContactListener.h"
#include <vector>

class Level
{
public:

	Level(sf::RenderWindow& window, Board& board);

	void run();
	void addObject(std::string type, sf::Vector2f pos)
	{
		auto unmovable = Factory<Unmovable>::instance().create(type, m_world, m_bodyDef, pos);
		if (unmovable)
		{
			m_unmovableObjVec.push_back(std::move(unmovable));
			return;
		}

		auto movable = Factory<Movable>::instance().create(type, m_world, m_bodyDef, pos);
		if (movable)
		{
			m_movableObjVec.push_back(std::move(movable));
			return;
		}

		auto platform = Factory<Platform>::instance().create(type, m_world, m_bodyDef, pos);
		if (platform)
		{
			m_platformVec.push_back(std::move(platform));
			return;
		}
		throw std::runtime_error(std::string("No factory handles " + type));
	}
	

private:

	void adjustView(sf::View&);
	void processEvent(const sf::Time&);
	void drawGraphics();

	bool m_lvlRunnig = true;
	sf::RenderWindow& m_window;
	Board& m_board;
	//SimplePlatform m_platform;		//temp
	Player m_player;
	std::unique_ptr<b2World> m_world;
	b2BodyDef m_bodyDef;
	std::vector<std::unique_ptr<Movable>> m_movableObjVec;	//uniqe_ptr???
	std::vector<std::unique_ptr<Unmovable>> m_unmovableObjVec;	//uniqe_ptr???
	std::vector<std::unique_ptr<Platform>> m_platformVec;	


	//in use for a specific operation!
	int m_windowDropAssister = 0;
};