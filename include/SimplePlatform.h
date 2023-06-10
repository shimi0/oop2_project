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


class SimplePlatform : public Platform, public Unmovable
{
public:
	SimplePlatform();

	void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef)
	{
		bodydef.type = b2_staticBody;
		bodydef.position.Set(sfmlToBox2D(600.f), sfmlToBox2D(1500.f));

		m_objectBody = world->CreateBody(&bodydef);

		b2PolygonShape playerBox;
		auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
		playerBox.SetAsBox(box.x, box.y);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &playerBox;
		fixtureDef.density = 1.0f;
		m_objectBody->CreateFixture(&fixtureDef);

		m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));

	}




private:

	
};
