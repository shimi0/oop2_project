#include "Player.h"

Player::Player()
	:Movable(Resources::instance().animationData(Resources::DoodleClassic), Direction::Right, m_sprite),
	GameObject(Resources::instance().animationData(Resources::DoodleClassic), Direction::Right, m_sprite)
{
}


void Player::loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef)
{
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(sfmlToBox2D(600.f), sfmlToBox2D(600.f));
	
	m_objectBody = world->CreateBody(&bodydef);

	b2PolygonShape playerBox;
	auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
	playerBox.SetAsBox(box.x, box.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &playerBox;
	fixtureDef.density = 1.0f;
	m_objectBody->CreateFixture(&fixtureDef);

	setPosition(box2DToSFML(m_objectBody->GetPosition()));

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
