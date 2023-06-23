#pragma once

#include "Resources.h"
#include "Animation.h"
#include "macros.h"
#include "SFML/Graphics.hpp"

class Button
{
public:
	Button(const AnimationData& data, Direction dir, sf::Sprite& sprite);
	~Button() = default;

	bool isPressed() const
	{
		return m_isPressed;
	}

	void press()
	{
		m_isPressed = true;
	}
	void release()
	{
		m_isPressed = false;
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(m_sprite);
	}

	bool contains(const sf::Vector2f& point) const
	{
		return m_sprite.getGlobalBounds().contains(point);
	}

	void looseFocus()
	{
		m_animation.direction(Direction::Up);
	}

	void gainFocus()
	{
		m_animation.direction(Direction::Down);
	}

protected:

	sf::Sprite m_sprite;
	Animation m_animation;


private:

	bool m_isPressed = false;

};