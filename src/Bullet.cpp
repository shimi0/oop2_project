#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position)
	:Movable(Resources::instance().animationData(Resources::Bullet), Direction::Up, m_sprite),
	 GameObject(Resources::instance().animationData(Resources::Bullet), Direction::Up, m_sprite),
	 m_position(position)
{}

void Bullet::loadObject(std::unique_ptr<b2World>&world, b2BodyDef & bodydef)
{
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(sfmlToBox2D(m_position.x), sfmlToBox2D(m_position.y));

	m_objectBody = world->CreateBody(&bodydef);

	b2PolygonShape playerBox;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	//m_sprite.setScale({ 2.f,2.f });
	auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width / 2.7, m_sprite.getGlobalBounds().height / 2);
	playerBox.SetAsBox(box.x, box.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &playerBox;
	fixtureDef.density = 2.5f;
	m_objectBody->CreateFixture(&fixtureDef);
	matchSptitePosToBody();
}

//------------------------------------

void Bullet::handleCollision(GameObject& obj)
{
	if(isMovingUp())
		obj.handleCollision(*this);
}

//------------------------------------

bool Bullet::isMovingUp() const
{
	return (m_objectBody->GetLinearVelocity().y < 0.0f);
}