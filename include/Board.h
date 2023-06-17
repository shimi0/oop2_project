#pragma once

#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Animation.h"

class Board
{
public:

	Board(sf::RenderWindow& window);
	void draw();
	void updateBGPos(const sf::Vector2f newPos)
	{
		m_sprite.setPosition(newPos);
	}


private:

	void drawBG();

	sf::RenderWindow& m_window;
	sf::Sprite m_sprite;
	Animation m_animation;
};