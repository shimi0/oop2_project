#include "Enemy.h"

Enemy::Enemy()
{}

//--------------------------------------

void Enemy::handleCollision(Bullet& obj)
{
	m_lives--;
	if (m_lives == 0) {
		m_isAlive = false;
		m_sprite.setColor(sf::Color::Transparent);
	}
}