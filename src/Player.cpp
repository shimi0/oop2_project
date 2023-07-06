#include "Player.h"

Player::Player()
	:Movable(Resources::instance().animationData(Resources::DoodleClassic), Direction::Right, m_sprite),
	GameObject(Resources::instance().animationData(Resources::DoodleClassic), Direction::Right, m_sprite),
	m_basePosition(sf::Vector2f(WIN_SIZE_X,WIN_SIZE_Y)),
	m_animationDeathStars(Resources::instance().animationData(Resources::DeathStars), Direction::Stay, m_spriteDeathStars)
{
	m_sound.setBuffer(AudioResources::Instance().getSound("jump.wav"));
	m_soundDeath.setBuffer(AudioResources::Instance().getSound("death_fall.wav"));
}

//------------------------------------------------------------

void Player::animate(const sf::Time & deltaTime)
{
	m_isDying ? playDyingBehavior() : matchSptitePosToBody();

	if (!m_isAlive) deathAnimation(deltaTime);
	if (m_objectBody->GetLinearVelocity().y == 0.f) m_animation.updateBasedOnCommand();

	//move to a diff func
	if (m_isUsingPropellerHat) {
		jump(0.5);
		if (m_clock.getElapsedTime().asSeconds() > PROPELLER_HAT_TIME)
			m_isUsingPropellerHat = false;
	}
	if (m_isUsingJetPack)
		if (m_clock.getElapsedTime().asSeconds() > JETPACK_TIME)
			m_isUsingJetPack = false;
}

//------------------------------------------------------------

void Player::drawStars(sf::RenderWindow& window)
{
	if (m_wasDying) return;
	window.draw(m_spriteDeathStars);
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

void Player::handleCollision(Platform& obj)
{
	if (isMovingUp()) return;

	m_sound.play();
	jump(1);
	m_animation.updateBasedOnCommand();
	m_basePosition = sf::Vector2f(obj.getPosition());
	m_score = std::abs(obj.getPosition().y - WIN_SIZE_Y);
	m_isInvulnerable = false;
	obj.handleCollision(*this);
}

//------------------------------------------------------------

void Player::handleCollision(BlackHoleEnemy& obj)
{
	if (m_isInvulnerable) return;
	m_sprite.setPosition(obj.getPosition());
	m_isDying = true;
}

//------------------------------------------------------------

void Player::handleCollision(Enemy& obj)
{
	if(!m_isInvulnerable)
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
	m_animation.direction(Direction::Left);
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

void Player::deathAnimation(const sf::Time& deltaTime)
{
	if (m_soundDeath.getStatus() != sf::Sound::Playing && !m_wasDying && !m_hasSoundBeenPlayed) {
		m_soundDeath.play();
		m_hasSoundBeenPlayed = true;
	}
	m_animationDeathStars.updateBasedOnTime(deltaTime);
	m_spriteDeathStars.setPosition(m_sprite.getPosition().x, m_sprite.getGlobalBounds().top);
}

//------------------------------------------------------------

void Player::loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef)
{
	Movable::defineBody(world, bodydef, { 400.0f, 1500.0f });
	b2PolygonShape playerBox;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale({ 2.f,2.f });
	auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width / 2.7, m_sprite.getGlobalBounds().height / 2);
	playerBox.SetAsBox(box.x, box.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &playerBox;
	fixtureDef.density = 9.5f;
	m_objectBody->SetGravityScale(1.5);
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
			case sf::Keyboard::Space:	shootBullet();																					return;
			default:																													return;
		}		
	}
	//dont stay with the nose up
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
		m_animation.direction(Direction::Left);

	m_direction = Direction::Stay;
	step(deltaTime);
}

//------------------------------------------------------------

void Player::kill()
{
	if (!m_isAlive) return;
	jump(0.5);
	m_isAlive = false;
}

//------------------------------------------------------------

sf::Vector2f Player::getBasePosition() const
{
	return m_basePosition;
}

//------------------------------------------------------------

bool Player::isAlive() const
{
	return m_isAlive;
}

//------------------------------------------------------------

bool Player::isDying() const
{
	return m_isDying;
}

//------------------------------------------------------------

void Player::playDyingBehavior()
{
	m_sprite.rotate(5);
	m_sprite.scale({ 0.98,0.98 });

	if (m_sprite.getScale().x < 0.1) {
		m_isAlive = false;
		m_wasDying = true;
	}
}

//------------------------------------------------------------

bool Player::hasShotBullet() const
{
	return m_hasShotBullet;
}

//------------------------------------------------------------

void Player::useBullet()
{
	m_hasShotBullet = false;
}

//------------------------------------------------------------

bool Player::isAllowedToUseGift() const
{
	return !m_isUsingJetPack && !m_isUsingPropellerHat;
}

//------------------------------------------------------------

int Player::getScore() const
{
	return m_score;
}

//------------------------------------------------------------

void Player::crossWindow()
{
	auto newPos = m_objectBody->GetPosition();
	if (getPosition().x < 0)
		newPos = b2Vec2(sfmlToBox2D(WIN_SIZE_X), m_objectBody->GetPosition().y);

	if (getPosition().x > WIN_SIZE_X)
		newPos = b2Vec2(0, m_objectBody->GetPosition().y);

	m_objectBody->SetTransform(newPos, m_objectBody->GetAngle());
}

//------------------------------------------------------------

void Player::shootBullet()
{
	if (!m_isUsingJetPack && !m_isUsingPropellerHat && !m_isDying && m_isAlive) {
		if (m_bulletsClock.getElapsedTime().asMilliseconds() < SHOOTING_FREQUENCY_MIN) return;
		m_bulletsClock.restart();
		m_animation.direction(Direction::Up);
		m_direction = Direction::Up;
		m_hasShotBullet = true;
	}
}