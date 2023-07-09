#pragma once

#include "macros.h"
#include "SFML/Graphics.hpp"
#include "Board.h"

//handles the window view. has specific behaviors.

const int FALL_DOWN_OFFSET = 18;

class ViewManager
{
public:

	ViewManager();

	//falling down affect
	bool fallDownAdjustment(Board& board, float BgPosY);

	//maove based on a position
	void basePointAdjustment(Board& board, const float gameViewY, const float boardY);

	//move based on - player reached a top window limit
	void reachedLimitAdjustment(Board& board, const float y_offset);
	void setView(sf::RenderWindow& window);

private:

	sf::View m_view;

	int m_fallDownAssister = 0;
};