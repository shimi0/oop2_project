#pragma once

#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Player.h"
#include "Bullet.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "StaticPlatform.h"
#include "ContactListener.h"
#include <vector>
#include "ViewManager.h"
#include "Gift.h"

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

	void addBullet()
	{
		index++;
		index %= 20;

		//replacing the oldest bullet with a new one. (instead of deleting and inserting a new one...)
		if (m_bullers.size() >= MAX_BULLETS)
		{
			m_bullers[index] = std::make_unique<Bullet>(m_player.getPosition());
			m_bullers[index]->loadObject(m_world, m_bodyDef);
		}
		else //first 20 bullet - "init" the vector
		{
			auto bullet = std::make_unique<Bullet>(m_player.getPosition());
			m_bullers.emplace_back(std::move(bullet));
			m_bullers[m_bullers.size() - 1]->loadObject(m_world, m_bodyDef);
		}
	}
	
	int index = 0;
private:

	//return the cur global cords. the top of the window.
	float getGlobalCordsY();
	void stepWorld(const sf::Time& deltaTime);
	void animateObjects(const sf::Time& deltaTime);
	void loadLevelData(ContactListener& contactListener);
	void isPlayerInWindow();
	void adjustView(ViewManager&);
	void processEvent(const sf::Time&);
	void drawGraphics();
	void handleBulletShooting();

	std::unique_ptr<b2World> m_world;
	b2BodyDef m_bodyDef;

	bool m_lvlRunnig = true;
	sf::RenderWindow& m_window;
	Board& m_board;

	Player m_player;
	std::vector<std::unique_ptr<Movable>> m_movableObjVec;
	std::vector<std::unique_ptr<Unmovable>> m_unmovableObjVec;
	std::vector<std::unique_ptr<Platform>> m_platformVec;	
	std::vector<std::unique_ptr<Bullet>>  m_bullers;

	//in use for a specific operation!
	int m_windowDropAssister = 0;
};