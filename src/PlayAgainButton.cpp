#include "PlayAgainButton.h"

PlayAgainButton::PlayAgainButton()
	:Button(Resources::instance().animationData(Resources::PlayAgainButton), Direction::Up, m_sprite)
{

	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.scale(2, 2);
	m_sprite.setPosition(WIN_SIZE_X  / 2, WIN_SIZE_Y * 7 / 10);
}
