#pragma once

#include "GameObject.h"

class Movable : virtual public GameObject
{
public:
	Movable(const AnimationData& data, Direction dir, sf::Sprite& sprite);
	virtual ~Movable() = 0 {}
	virtual void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef) override {};

	void matchSptitePosToBody();

private:

};