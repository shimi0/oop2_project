#include "PauseButton.h"

PauseButton::PauseButton()
	:Button(Resources::instance().animationData(Resources::PauseButton), Direction::Stay, m_sprite)
{
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.scale(2, 2);
}
