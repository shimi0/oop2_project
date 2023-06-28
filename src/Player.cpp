#include "Player.h"


Player::Player()
	:Movable(Resources::instance().animationData(Resources::DoodleClassic), Direction::Right, m_sprite),
	GameObject(Resources::instance().animationData(Resources::DoodleClassic), Direction::Right, m_sprite),
	m_basePosition(sf::Vector2f(WIN_SIZE_X,WIN_SIZE_Y)),
	m_animationDeathStars(Resources::instance().animationData(Resources::DeathStars), Direction::Stay, m_spriteDeathStars)
{}

//------------------------------------------------------------

void Player::animate(const sf::Time & deltaTime)
{
	if (m_isDying)
		playDyingBehavior();
	else
		matchSptitePosToBody();

	if (!m_isAlive)
		deathAnimation(deltaTime);

	if (m_objectBody->GetLinearVelocity().y == 0.f)
		m_animation.updateBasedOnCommand();


	//move to a diff func
	if (m_isUsingPropellerHat)
		if (m_clock.getElapsedTime().asSeconds() > PROPELLER_HAT_TIME)
			m_isUsingPropellerHat = false;

	if (m_isUsingJetPack)
		if (m_clock.getElapsedTime().asSeconds() > JETPACK_TIME)
			m_isUsingJetPack = false;
	if(m_isUsingPropellerHat)
		jump(0.5);
}

//------------------------------------------------------------

bool Player::isMovingUp() const
{
	return (m_objectBody->GetLinearVelocity().y < 0.0f);
}

//------------------------------------------------------------

void Player::handleCollision(GameObject& obj)
{
	obj.handleCollision(*this);
}

//------------------------------------------------------------

void Player::handleCollision(Unmovable& obj)
{
	obj.handleCollision(*this);
}

//------------------------------------------------------------

void Player::handleCollision(Platform& obj)
{
	if (isMovingUp())
		return;

	jump(1);
	m_animation.updateBasedOnCommand();
	m_basePosition = sf::Vector2f(obj.getPosition());
	//set to false once the player landed on a platform
	m_isInvulnerable = false;
}

//------------------------------------------------------------

void Player::handleCollision(BlackHoleEnemy& obj)
{
	if (m_isInvulnerable)
		return;
	m_sprite.setPosition(obj.getPosition());
	m_isDying = true;

}

//------------------------------------------------------------

void Player::handleCollision(FlyingEnemy& obj)
{
	if(!m_isInvulnerable)
		m_isAlive = false;
}

//------------------------------------------------------------

void Player::handleCollision(FireMonster& obj)
{
	if (!m_isInvulnerable)
		m_isAlive = false;
}

//------------------------------------------------------------

void Player::handleCollision(SpringGift& obj)
{
	jump(2.5f);
	m_isInvulnerable = true;
	m_animation.updateBasedOnCommand();
}

//------------------------------------------------------------

void Player::handleCollision(JetPack& obj)
{
	if (m_isUsingJetPack || m_isUsingPropellerHat) return;
	m_clock.restart();
	m_direction == Direction::Left;
	jump(5);
	m_isUsingJetPack = true;
	m_isInvulnerable = true;
}

//------------------------------------------------------------

void Player::handleCollision(PropellerHat& obj)
{
	if (m_isUsingJetPack || m_isUsingPropellerHat) return;

	m_clock.restart();
	m_isUsingPropellerHat = true;
	m_isInvulnerable = true;
	jump(0.5);
}

//------------------------------------------------------------

void Player::loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef)
{
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(sfmlToBox2D(400.0f), sfmlToBox2D(1500.f));
	
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
	matchSptitePosToBody();

	m_spriteDeathStars.setOrigin(m_spriteDeathStars.getGlobalBounds().width / 2, m_spriteDeathStars.getGlobalBounds().height / 2);
	m_spriteDeathStars.setScale({ 2.f,2.f });
}

//------------------------------------------------------------

void Player::jump(const float jumpHeightAmount)
{
	if (!m_isJumpinAllowed) return;

	b2Vec2 currentVelocity = m_objectBody->GetLinearVelocity();
	currentVelocity.y = -JUMP_HEIGHT * jumpHeightAmount;	
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
		default:                                               break;
	}
	updatePositionX(desiredVelocity.x);
	crossWindow();
}

//------------------------------------------------------------

void Player::processKeyInput(const sf::Event& event, const sf::Time& deltaTime)
{

	if (event.type == sf::Event::KeyPressed) {
 		switch (event.key.code)
		{
			case sf::Keyboard::Right:
			case sf::Keyboard::D:       m_animation.direction(Direction::Right);	m_direction = Direction::Right; step(deltaTime);	return;
			case sf::Keyboard::Left:
			case sf::Keyboard::A:       m_animation.direction(Direction::Left);	    m_direction = Direction::Left; step(deltaTime);		return;
			case sf::Keyboard::Space:	
				if (!m_isUsingJetPack && !m_isUsingPropellerHat) {
					m_animation.direction(Direction::Up);	    
					m_direction = Direction::Up;
					m_hasShotBullet = true;
				}
				return;
			default:																													return;
		}		
	}
	//dont stay with the nose up
	if (event.type == sf::Event::KeyReleased)
		if(event.key.code == sf::Keyboard::Space)
			m_animation.direction(Direction::Left);

	m_direction = Direction::Stay;
	step(deltaTime);
}

//------------------------------------------------------------

void Player::crossWindow()
{
	auto newPos = b2Vec2();
	if (getPosition().x < 0)
	{
		newPos = b2Vec2(sfmlToBox2D(WIN_SIZE_X), m_objectBody->GetPosition().y);
		m_objectBody->SetTransform(newPos, m_objectBody->GetAngle());
	}

	if (getPosition().x > WIN_SIZE_X) 
	{
		newPos = b2Vec2(0, m_objectBody->GetPosition().y);
		m_objectBody->SetTransform(newPos, m_objectBody->GetAngle());
	}
}