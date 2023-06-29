#pragma once

#include "Platform.h"
#include "Unmovable.h"
#include "Resources.h"
#include "Animation.h"
#include "GameObject.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "CordinatesConverter.h"
#include "Factory.h"



class OneJumpPlatform : public Platform, public Unmovable
{
public:
	OneJumpPlatform(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos);
	virtual bool isMovable() const override;

	virtual void animate(const sf::Time& deltaTime) override;

private:

};
