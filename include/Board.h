#pragma once

#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Animation.h"

class Board
{
public:

	Board(sf::RenderWindow& window);
	void draw();


private:

	void drawBG();

	sf::RenderWindow& m_window;
	sf::Sprite m_sprite;
	Animation m_animation;
};