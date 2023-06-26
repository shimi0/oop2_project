#include "Board.h"

Board::Board(sf::RenderWindow& window)
	:m_window(window), m_animationBG(Resources::instance().animationData(Resources::BackGroundClassic), Direction::Stay, m_spriteBG),
	 m_scoreTopAnimation(Resources::instance().animationData(Resources::ScoreTopClassic), Direction::Stay, m_scoreTop),
	 m_pauseScreenAnimation(Resources::instance().animationData(Resources::PauseScreen), Direction::Stay, m_PauseScreen),
	 m_pauseButton()
{}

//------------------------------------------------

void Board::draw()
{
	drawBG();
	//drawScoreTop();
}

void Board::updateBGPos(const sf::Vector2f newPos)
{
	m_spriteBG.setPosition(newPos);
	m_scoreTop.setPosition(newPos);
	m_PauseScreen.setPosition(newPos);
	m_pauseButton.setPosition(sf::Vector2f( WIN_SIZE_X * 20 / 22, m_scoreTop.getPosition().y + m_scoreTop.getGlobalBounds().height / 2.8));
	
}

//------------------------------------------------
																															//==|
void Board::drawBG()																										//==|
{																															//==|
		//----------TO_DO: biger scale for the bg. only in my pc- bigger resolutin. change!!!!----------------------------------|

	m_spriteBG.scale(640 * 2 / m_spriteBG.getGlobalBounds().width, 1024 * 2 / m_spriteBG.getGlobalBounds().height);
	m_window.draw(m_spriteBG);
	m_spriteBG.setScale(1, 1);
}

void Board::drawScoreTop()
{
	
	m_scoreTop.scale(640 * 2 / m_scoreTop.getGlobalBounds().width, (WIN_SIZE_Y / 18) / m_scoreTop.getGlobalBounds().height);
	m_window.draw(m_scoreTop);
	m_pauseButton.draw(m_window);
	
}



