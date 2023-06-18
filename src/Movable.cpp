#include "Movable.h"

Movable::Movable(const AnimationData& data, Direction dir, sf::Sprite& sprite)
	:GameObject(data, dir, sprite)
{}

//-------------------------------------------

void Movable::matchSptitePosToBody()
{
	m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));
}

//-------------------------------------------

void Movable::updatePositionX(const float& desiredVelocity)
{
	b2Vec2 currentVelocity = m_objectBody->GetLinearVelocity();
	float velocityChange = desiredVelocity - currentVelocity.x;
	float impulse = m_objectBody->GetMass() * velocityChange;
	m_objectBody->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0.0f), true);
}

//-------------------------------------------

void Movable::updatePositionY(const float& desiredVelocity)
{
	b2Vec2 currentVelocity = m_objectBody->GetLinearVelocity();
	float velocityChange = desiredVelocity - currentVelocity.y;
	float impulse = m_objectBody->GetMass() * velocityChange;
	m_objectBody->ApplyLinearImpulseToCenter(b2Vec2(0.0f, impulse), true);
}