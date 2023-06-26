#pragma once

#include "macros.h"
#include "SFML/Graphics.hpp"
#include "Board.h"

const int FALL_DOWN_OFFSET = 18;

class ViewManager
{
public:
	ViewManager()
	{
		m_view.setSize(sf::Vector2f(WIN_SIZE_X, WIN_SIZE_Y));
		m_view.setCenter(sf::Vector2f(WIN_SIZE_X / 2, WIN_SIZE_Y / 2));
	}

	bool fallDownAdjustment(Board& board, float BgPosY)
	{
		m_fallDownAssister++;
		if (m_fallDownAssister * FALL_DOWN_OFFSET < WIN_SIZE_Y * 2)
		{
			m_view.move(0, FALL_DOWN_OFFSET);
			board.updateBGPos(sf::Vector2f(0, BgPosY + FALL_DOWN_OFFSET));
			return true;
		}
		else
			return false;
	}
	void basePointAdjustment(Board& board, const float gameViewY, const float boardY)
	{
		m_view.setCenter(m_view.getCenter().x, m_view.getCenter().y + gameViewY);
		board.updateBGPos(sf::Vector2f(0, boardY));
	}

	void reachedLimitAdjustment(Board& board, const float y_offset)
	{
		m_view.setCenter(m_view.getCenter().x, y_offset);
		board.updateBGPos(sf::Vector2f(0, y_offset - WIN_SIZE_Y / 2));
	}

	void setView(sf::RenderWindow& window)
	{
		window.setView(m_view);
	}


private:
	sf::View m_view;

	int m_fallDownAssister = 0;
};