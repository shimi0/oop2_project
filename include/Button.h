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

	void draw(sf::RenderWindow& window) const
	{
		window.draw(m_sprite);
	}

	bool contains(const sf::Vector2f& point) const
	{
		return m_sprite.getGlobalBounds().contains(point);
	}

	//had to make the virtual for a specific butoon(score) that i could only use diff size sprites.
	virtual void looseFocus()
	{
		m_animation.direction(Direction::Up);
	}

	virtual void gainFocus()
	{
		m_animation.direction(Direction::Down);
	}

	void setPosition(const sf::Vector2f& position)
	{
		m_sprite.setPosition(position);
	}

protected:

	sf::Sprite m_sprite;
	Animation m_animation;


private:

	bool m_isPressed = false;

};