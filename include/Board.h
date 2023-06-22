#pragma once

#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Animation.h"
#include "box2d/box2d.h"
#include "macros.h"

class Board
{
public:

	Board(sf::RenderWindow& window);
	void draw();
	void updateBGPos(const sf::Vector2f newPos)
	{
		m_sprite.setPosition(newPos);
	}

	void resetBoardPosition()
	{
		updateBGPos({ 0,0 });
	}
private:

	void drawBG();

	sf::RenderWindow& m_window;
	sf::Sprite m_sprite;
	Animation m_animation;
	
};