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

//runs a game until failint or winning

class Level
{
public:

	Level(sf::RenderWindow& window, Board& board);

	void updateScore();
	void run();

	//in use before the playing screen sows up
	void addObject(std::string type, sf::Vector2f pos);
	void addBullet();

private:

	//in use for the bullets vector
	int index = 0;

	//return the cur global cords. the top of the window.
	float getGlobalCordsY();

	//move the game a step
	void stepWorld(const sf::Time& deltaTime);
	void animateObjects(const sf::Time& deltaTime);

	void loadLevelData(ContactListener& contactListener);
	void isPlayerInWindow();

	//adjusint the view window in specific cases
	void adjustView(ViewManager&);

	void processEvent(const sf::Time&);

	void drawGraphics();
	void handleBulletShooting();
	void endOfLevel();

	//box2d objects
	std::unique_ptr<b2World> m_world;

	//helps to create all the objects in the game
	b2BodyDef m_bodyDef;

	bool m_lvlRunnig = true;
	sf::RenderWindow& m_window;
	Board& m_board;

	//all game objects
	Player m_player;
	std::vector<std::unique_ptr<Movable>> m_movableObjVec;
	std::vector<std::unique_ptr<Unmovable>> m_unmovableObjVec;
	std::vector<std::unique_ptr<Platform>> m_platformVec;	
	std::vector<std::unique_ptr<Bullet>>  m_bullers;

	//in use for a specific operation!
	int m_windowDropAssister = 0;

	//holds the end of level position. 2000 is only to initialize
	float m_endLvlPos = 2000;
};