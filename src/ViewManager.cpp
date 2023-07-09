#include "ViewManager.h"

ViewManager::ViewManager()
{
	m_view.setSize(sf::Vector2f(WIN_SIZE_X, WIN_SIZE_Y));
	m_view.setCenter(sf::Vector2f(WIN_SIZE_X / 2, WIN_SIZE_Y / 2));
}

//----------------------------------------

bool ViewManager::fallDownAdjustment(Board& board, float BgPosY)
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

//----------------------------------------

void ViewManager::basePointAdjustment(Board& board, const float gameViewY, const float boardY)
{
	m_view.setCenter(m_view.getCenter().x, m_view.getCenter().y + gameViewY);
	board.updateBGPos(sf::Vector2f(0, boardY));
}

//----------------------------------------

void ViewManager::reachedLimitAdjustment(Board& board, const float y_offset)
{
	m_view.setCenter(m_view.getCenter().x, y_offset);
	board.updateBGPos(sf::Vector2f(0, y_offset - WIN_SIZE_Y / 2));
}

//----------------------------------------

void ViewManager::setView(sf::RenderWindow& window)
{
	window.setView(m_view);
}