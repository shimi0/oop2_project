#pragma once

#include "GameObject.h"

class Movable : public GameObject
{
public:
	Movable(const AnimationData& data, Direction dir, sf::Sprite& sprite);
	virtual ~Movable() = 0 {}


private:
};