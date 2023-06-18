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

	void step(const sf::Time& deltaTime) override
	{
		//m_direction = Direction::Right;

		if(box2DToSFML(m_objectBody->GetPosition()).x  < 150.f)
			m_direction = Direction::Right;

		if(box2DToSFML(m_objectBody->GetPosition()).x > (WIN_SIZE_X - 150))
			m_direction = Direction::Left;
		float desiredVelocity = 0.0f;
		switch (m_direction)
		{
			case Direction::Right: desiredVelocity = 3.0f;       break;
			case Direction::Left:  desiredVelocity = -3.0f;      break;
			case Direction::Stay:  desiredVelocity = 0.0f;       break;
			default:                                             break;
		}
		b2Vec2 currentVelocity = m_objectBody->GetLinearVelocity();
		float velocityChange = desiredVelocity - currentVelocity.x;
		float impulse = m_objectBody->GetMass() * velocityChange;
		m_objectBody->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0.0f), true);
		matchSptitePosToBody();

	}

private:
	void loadObject();

};
