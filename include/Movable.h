#pragma once

#include "GameObject.h"

//a base class for all the moving objects

class Movable : virtual public GameObject
{
public:

	Movable(const AnimationData& data, Direction dir, sf::Sprite& sprite);
	virtual ~Movable() = 0 {}
	virtual void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef) override {};

	//matching the graphic body to the box2d body
	void matchSptitePosToBody();

	virtual void step(const sf::Time& deltaTime) = 0;
	virtual void setPosition(const sf::Vector2f& pos ) {}

protected:

	void defineBody(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos);

	//object current direction. NOTE: no guard for horizontal to set with vertical...
	Direction m_directionHorizontal = Direction::Right;
	Direction m_directionVertical = Direction::Up;

	//any direction
	Direction m_direction = Direction::Up;

	//sets new horizontal position based on a desired velocity
	void updatePositionX(const float& desiredVelocity);

	//sets new vertical position based on a desired velocity
	void updatePositionY(const float& desiredVelocity);

private:
};