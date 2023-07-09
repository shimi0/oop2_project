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

//an exploding platform. explodes after a few seonds.
//currently set in Level class to explode only after shows up on the screen view

class ExplodingPlatform : public Platform, public Unmovable
{
public:

	ExplodingPlatform(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos);

	virtual void animate(const sf::Time&) override;
	virtual bool isMovable() const override;

private:

	sf::Sound m_sound;
	bool m_explode = false;
	bool m_hasSoundBeenPlayed = false;
};
