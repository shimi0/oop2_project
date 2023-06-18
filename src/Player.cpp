#include "Player.h"


Player::Player()
	:Movable(Resources::instance().animationData(Resources::DoodleClassic), Direction::Right, m_sprite),
	GameObject(Resources::instance().animationData(Resources::DoodleClassic), Direction::Right, m_sprite),
	m_basePosition(sf::Vector2f(WIN_SIZE_X,WIN_SIZE_Y))
{}

//------------------------------------------------------------

bool Player::isMovingUp() const
{
	return (m_objectBody->GetLinearVelocity().y < 0.0f);
}

//------------------------------------------------------------

void Player::handleCollision(GameObject& obj)
{
	jump();
	m_animation.updateBasedOnCommand();
	m_basePosition = sf::Vector2f(obj.getPosition());
}

//------------------------------------------------------------

void Player::loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef)
{
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(sfmlToBox2D(600.f), sfmlToBox2D(600.f));
	
	m_objectBody = world->CreateBody(&bodydef);

	b2PolygonShape playerBox;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale({ 2.f,2.f });
	auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width / 2.7, m_sprite.getGlobalBounds().height / 2);
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

void Player::step(const sf::Time& deltaTime)
{
	auto desiredVelocity = b2Vec2(0.0f, 0.0f);
	switch (m_direction)
	{
		case Direction::Right: desiredVelocity.x = 6.0f;       break;
		case Direction::Left:  desiredVelocity.x = -6.0f;      break;
		case Direction::Stay:  desiredVelocity.x = 0.0f;       break;
		default:                                             break;
	}
	updatePositionX(desiredVelocity.x);

}

//------------------------------------------------------------

void Player::processKeyInput(const sf::Event& event, const sf::Time& deltaTime)
{
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code)
		{
			case sf::Keyboard::Right:
			case sf::Keyboard::D: m_animation.direction(Direction::Right);	m_direction = Direction::Right; step(deltaTime);	return;
			case sf::Keyboard::Left:
			case sf::Keyboard::A: m_animation.direction(Direction::Left);	m_direction = Direction::Left; step(deltaTime);		return;
			default:																											return;
		}		
	}
	m_direction = Direction::Stay;
	step(deltaTime);
}
