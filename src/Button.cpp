#include "Button.h"

Button::Button(const AnimationData& data, Direction dir, sf::Sprite& sprite)
	:m_animation(data, dir, sprite)
{

}

//---------------------------------------

bool Button::isPressed() const
{
	return m_isPressed;
}

//---------------------------------------

void Button::press()
{
	m_isPressed = true;
}

//---------------------------------------

void Button::release()
{
	m_isPressed = false;
}

//---------------------------------------

void Button::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

//---------------------------------------

bool Button::contains(const sf::Vector2f& point) const
{
	return m_sprite.getGlobalBounds().contains(point);
}

//---------------------------------------

//had to make the virtual for a specific butoon(score) that i could only use diff size sprites.
void Button::looseFocus()
{
	m_animation.direction(Direction::Up);
}

//---------------------------------------

void Button::gainFocus()
{
	m_animation.direction(Direction::Down);
}

//---------------------------------------

void Button::setPosition(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
}