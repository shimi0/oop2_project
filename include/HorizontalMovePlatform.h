#pragma once

#include "Platform.h"
#include "Movable.h"
#include "Resources.h"
#include "Animation.h"
#include "GameObject.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "CordinatesConverter.h"
#include "Factory.h"



class HorizontalMovePlatform : public Platform, public Movable
{
public:
	HorizontalMovePlatform(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos);

	void step(const sf::Time& deltaTime) override;
	

private:
	void loadObject();

};
