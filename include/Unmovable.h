#pragma once

#include "GameObject.h"

class Unmovable : virtual public GameObject
{
public:
	Unmovable(const AnimationData& data, Direction dir, sf::Sprite& sprite);
	virtual ~Unmovable() = 0 {}
	void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef) override {};


	//virtual void attachTo(const sf::Vector2f& position) {};
private:

};