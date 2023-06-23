#include "MenuButton.h"

MenuButton::MenuButton()
	:Button(Resources::instance().animationData(Resources::MenuButton), Direction::Up, m_sprite)
{

	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.scale(2, 2);
	m_sprite.setPosition(WIN_SIZE_X * 5 / 7, WIN_SIZE_Y * 8/ 10);
}
