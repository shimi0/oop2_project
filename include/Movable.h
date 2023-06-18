#pragma once

#include "GameObject.h"

class Movable : virtual public GameObject
{
public:
	Movable(const AnimationData& data, Direction dir, sf::Sprite& sprite);
	virtual ~Movable() = 0 {}
	virtual void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef) override {};

	void matchSptitePosToBody();
	virtual void step(const sf::Time& deltaTime) = 0;
	

protected:

	//object current direction
	Direction m_direction = Direction::Right;

	//sets new horizontal position based on a desired velocity
	void updatePositionX(const float& desiredVelocity);

	//sets new vertical position based on a desired velocity
	void updatePositionY(const float& desiredVelocity);



private:


};