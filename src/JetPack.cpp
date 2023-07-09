#include "JetPack.h"

JetPack::JetPack(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	:Gift(Resources::instance().animationData(Resources::JetPack), Direction::Stay, m_sprite),
	GameObject(Resources::instance().animationData(Resources::JetPack), Direction::Stay, m_sprite),
	Movable(Resources::instance().animationData(Resources::JetPack), Direction::Stay, m_sprite)
{
	defineBody(world, bodydef, pos);
	Gift::loadObject();
	m_sound.setBuffer(AudioResources::Instance().getSound("jetpack2.wav"));
}

//----------------------------------------

void JetPack::handleCollision(Player& obj)
{
	if (!obj.isAllowedToUseGift())
		return;

	m_sound.play();
	m_animation.direction(Direction::Left);
	m_isInUse = true;
	m_clock.restart();
	obj.handleCollision(*this);
	m_playerGlobalBounds = obj.getGlobalBounds();
}

//----------------------------------------

void JetPack::animate(const sf::Time& deltaTime)
{
	if (m_clock.getElapsedTime().asSeconds() > JETPACK_TIME && m_isInUse)
	{
		m_isInUse = false;
		m_objectBody->SetEnabled(false);
		m_sprite.setColor(sf::Color::Transparent);
	}

	if (m_isInUse)
		m_animation.updateBasedOnTime(deltaTime);
}

//----------------------------------------

void JetPack::setPosition(const sf::Vector2f& pos)
{
	if (!m_isInUse) return;
	sf::Vector2f positinon = { pos.x + m_playerGlobalBounds.width / 3, pos.y + 30 };
	//curr only the sprtie moves to avoid multiple collisions
	//m_objectBody->SetTransform(sfmlToBox2D(positinon), m_objectBody->GetAngle());
	m_sprite.setPosition(positinon);
}

//----------------------------------------

static auto registerIt = Factory<Movable>::instance().registerType(
	"JetPack",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Movable>
	{
		return std::make_unique<JetPack>(world, bodydef, pos);
	}
);

//----------------------------------------