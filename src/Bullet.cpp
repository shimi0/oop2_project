#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position)
	:Movable(Resources::instance().animationData(Resources::Bullet), Direction::Up, m_sprite),
	 GameObject(Resources::instance().animationData(Resources::Bullet), Direction::Up, m_sprite),
	 m_position(position)
{}

//------------------------------------

void Bullet::loadObject(std::unique_ptr<b2World>&world, b2BodyDef & bodydef)
{
	defineBody(world, bodydef, m_position);

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

void Bullet::step(const sf::Time&)
{
	matchSptitePosToBody();
	if (m_hasBeenshot)
		if (m_timeSinceShot.getElapsedTime().asSeconds() > BULLET_LIFE_TIME)
			m_hasFallen = true;
}

//------------------------------------

void Bullet::shoot()
{
	if (m_hasBeenshot) return;

	m_hasBeenshot = true;

	m_timeSinceShot.restart();
	float sideAngle = 0;
	int num = rand() % 7;
	switch (num)
	{
		case 0:	sideAngle = 0.0f;			break;
		case 1:	sideAngle = 0.03f;			break;
		case 2:	sideAngle = 0.06f;			break;
		case 3:	sideAngle = -0.03f;			break;
		case 4:	sideAngle = -0.06f;			break;
		case 5:	sideAngle = 0.09f;			break;
		case 6:	sideAngle = -0.09f;			break;
			default: break;
	}
	m_objectBody->ApplyLinearImpulseToCenter({ sideAngle, -2.4f }, true);
}
//------------------------------------

bool Bullet::hasFallen() const
{
	return m_hasFallen;
}

//------------------------------------

bool Bullet::isMovingUp() const
{
	return (m_objectBody->GetLinearVelocity().y < 0.0f);
}