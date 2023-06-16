#include "Player.h"

Player::Player()
	:Movable(Resources::instance().animationData(Resources::DoodleClassic), Direction::Right, m_sprite),
	GameObject(Resources::instance().animationData(Resources::DoodleClassic), Direction::Right, m_sprite),
	m_basePosition(sf::Vector2f(WIN_SIZE_X,WIN_SIZE_Y))
{}

//------------------------------------------------------------

void Player::loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef)
{
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(sfmlToBox2D(600.f), sfmlToBox2D(600.f));
	
	m_objectBody = world->CreateBody(&bodydef);

	b2PolygonShape playerBox;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale({ 2.f,2.f });
	auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width / 2.5, m_sprite.getGlobalBounds().height / 2);
	playerBox.SetAsBox(box.x, box.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &playerBox;
	fixtureDef.density = 2.5f;
	m_objectBody->CreateFixture(&fixtureDef);
}

//------------------------------------------------------------

void Player::jump()
{
	b2Vec2 currentVelocity = m_objectBody->GetLinearVelocity();
	currentVelocity.y = -JUMP_HEIGHT;
	m_objectBody->SetLinearVelocity(currentVelocity);
}

//------------------------------------------------------------

void Player::step(const Direction dir, const sf::Time& deltaTime)
{
	float desiredVelocity = 0.0f;
	switch (dir)
	{
		case Direction::Right: desiredVelocity = 6.0f;       break;
		case Direction::Left:  desiredVelocity = -6.0f;      break;
		case Direction::Stay:  desiredVelocity = 0.0f;       break;
		default:                                             break;
	}

	b2Vec2 currentVelocity = m_objectBody->GetLinearVelocity();
	float velocityChange = desiredVelocity - currentVelocity.x;
	float impulse = m_objectBody->GetMass() * velocityChange;
	m_objectBody->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0.0f), true);
}

//------------------------------------------------------------

void Player::processKeyInput(const sf::Event& event, const sf::Time& deltaTime)
{
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code)
		{
			case sf::Keyboard::Right:
			case sf::Keyboard::D: m_animation.direction(Direction::Right);	step(Direction::Right, deltaTime);	return;
			case sf::Keyboard::Left:
			case sf::Keyboard::A: m_animation.direction(Direction::Left);	step(Direction::Left, deltaTime);	return;
			default:																							return;
		}
	}
	step(Direction::Stay, deltaTime);
}
