#include "Player.h"

Player::Player()
	:Movable(Resources::instance().animationData(Resources::DoodleClassic), Direction::Right, m_sprite)
{
}

void Player::loadPlayer(std::unique_ptr<b2World>& world, b2BodyDef& bodydef)
{
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(40.f / SCALE, 40.f / SCALE);
	setPosition({ 0,0 });
	m_playerBody = world->CreateBody(&bodydef);

	b2PolygonShape playerBox;
	playerBox.SetAsBox(20.0f / SCALE, 20.0f / SCALE);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &playerBox;
	fixtureDef.density = 1.0f;
	m_playerBody->CreateFixture(&fixtureDef);

}

void Player::processKeyInput(const sf::Event& event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Right:
	case sf::Keyboard::D: m_animation.direction(Direction::Right);		break;
	case sf::Keyboard::Left:
	case sf::Keyboard::A: m_animation.direction(Direction::Left);		break;
	default:
		break;
	}
}
