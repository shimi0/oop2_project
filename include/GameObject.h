#pragma once

#include "Resources.h"
#include "Animation.h"
#include "Direction.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "CordinatesConverter.h"
#include <iostream>

class Platform;
class Player;

class GameObject
{
public:

	GameObject(const AnimationData& data, Direction dir, sf::Sprite& sprite);
	virtual ~GameObject() = 0 {}
	void draw(sf::RenderWindow& m_window);
	virtual void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef) = 0;
	virtual void handleCollision(GameObject& obj) {};

	bool isSameBody(const b2Body* other) const
	{
		return m_objectBody == other;
	}

	sf::Vector2f getPosition() const
	{
		return m_sprite.getPosition();
	}

protected:

	sf::Sprite m_sprite;
	Animation m_animation;
	b2Body* m_objectBody;
private:

	
	
};