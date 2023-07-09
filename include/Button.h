#pragma once

#include "Resources.h"
#include "Animation.h"
#include "macros.h"
#include "SFML/Graphics.hpp"

//a game button

class Button
{
public:
	Button(const AnimationData& data, Direction dir, sf::Sprite& sprite);
	~Button() = default;

	bool isPressed() const;
	void press();
	void release();

	void draw(sf::RenderWindow& window) const;

	bool contains(const sf::Vector2f& point) const;

	//had to make tose virtual for a specific butoon(score) that i could only find diff size sprites.
	virtual void looseFocus();
	virtual void gainFocus();

	void setPosition(const sf::Vector2f& position);

protected:

	sf::Sprite m_sprite;
	Animation m_animation;

private:

	bool m_isPressed = false;
};