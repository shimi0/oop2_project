
#include "PlayButton.h"

PlayButton::PlayButton()
	:Button(Resources::instance().animationData(Resources::PlayButton), Direction::Up, m_sprite)
{
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.scale(2, 2);
	m_sprite.setPosition(WIN_SIZE_X / 4, WIN_SIZE_Y / 3);
}