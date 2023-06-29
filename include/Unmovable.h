#pragma once

#include "GameObject.h"

class Unmovable : virtual public GameObject
{
public:
	Unmovable(const AnimationData& data, Direction dir, sf::Sprite& sprite);
	virtual ~Unmovable() = 0 {}
	void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef) override {};

protected:

	void defineBody(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos);

private:


};