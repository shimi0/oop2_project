#include "ScoreButton.h"

ScoreButton::ScoreButton()
	:Button(Resources::instance().animationData(Resources::ScoreButton), Direction::Up, m_sprite)
{
	m_sprite.setScale(4, 4);
	m_sprite.setPosition(WIN_SIZE_X * 2/ 7, WIN_SIZE_Y * 2/ 5);
}

//---------------------------------------------

void ScoreButton::looseFocus()
{
	Button::looseFocus();
	m_sprite.setScale(4, 4);
}

//---------------------------------------------

void ScoreButton::gainFocus()
{
	Button::gainFocus();
	m_sprite.setScale(2, 2);
}