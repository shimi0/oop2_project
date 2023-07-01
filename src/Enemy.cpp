#include "Enemy.h"

Enemy::Enemy()
{}

//--------------------------------------

void Enemy::loadObject()
{
	b2PolygonShape playerBox;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale({ 2.f,2.f });
	auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width / 5.0f, m_sprite.getGlobalBounds().height / 5.f);
	playerBox.SetAsBox(box.x, box.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &playerBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 10.0f;
	m_objectBody->CreateFixture(&fixtureDef);
	m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));
	m_objectBody->SetGravityScale(0.0f);
}
//--------------------------------------

void Enemy::handleCollision(Bullet& obj)
{
	m_lives--;
	if (m_lives == 0) {
		m_isAlive = false;
		m_clock.restart();

	}
}