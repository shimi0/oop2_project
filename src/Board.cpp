#include "Board.h"

Board::Board(sf::RenderWindow& window)
	:m_window(window), m_animation(Resources::instance().animationData(Resources::BackGroundClassic), Direction::Stay, m_sprite)
{}

//------------------------------------------------

void Board::draw()
{
	drawBG();
}

//------------------------------------------------
																															//==|
void Board::drawBG()																										//==|
{																															//==|
		//----------TO_DO: biger scale for the bg. only in my pc- bigger resolutin. change!!!!----------------------------------|

	m_sprite.scale(640 * 2 / m_sprite.getGlobalBounds().width, 1024 * 2 / m_sprite.getGlobalBounds().height);
	m_window.draw(m_sprite);
	m_sprite.setScale(1, 1);
}



