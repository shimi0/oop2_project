#include "PropellerHat.h"

PropellerHat::PropellerHat(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	:Gift(Resources::instance().animationData(Resources::PropellerHat), Direction::Stay, m_sprite),
	GameObject(Resources::instance().animationData(Resources::PropellerHat), Direction::Stay, m_sprite),
	Movable(Resources::instance().animationData(Resources::PropellerHat), Direction::Stay, m_sprite)
{
	defineBody(world, bodydef, pos);
	Gift::loadObject();
	m_sound.setBuffer(AudioResources::Instance().getSound("propeller3.wav"));
}

//----------------------------------------

void PropellerHat::handleCollision(Player& obj)
{
	if (!obj.isAllowedToUseGift())
		return;
	m_sound.play();
	m_animation.direction(Direction::Up);
	m_isInUse = true;
	m_clock.restart();
	obj.handleCollision(*this);
	m_playerGlobalBounds = obj.getGlobalBounds();
}

//----------------------------------------

void PropellerHat::animate(const sf::Time& deltaTime)
{
	if (m_clock.getElapsedTime().asSeconds() > PROPELLER_HAT_TIME && m_isInUse)
	{
		m_isInUse = false;
		m_objectBody->SetEnabled(false);
		m_sprite.setColor(sf::Color::Transparent);
	}

	if (m_isInUse)
		m_animation.updateBasedOnTime(deltaTime);
}

//----------------------------------------

void PropellerHat::setPosition(const sf::Vector2f& pos)
{
	if (!m_isInUse) return;
	sf::Vector2f positinon = { pos.x, pos.y - m_playerGlobalBounds.height / 3.2f };
	m_objectBody->SetTransform(sfmlToBox2D(positinon), m_objectBody->GetAngle());
	m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));
}

//----------------------------------------

static auto registerIt = Factory<Movable>::instance().registerType(
	"PropellerHat",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Movable>
	{
		return std::make_unique<PropellerHat>(world, bodydef, pos);
	}
);