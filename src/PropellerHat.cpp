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

static auto registerIt = Factory<Movable>::instance().registerType(
	"PropellerHat",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Movable>
	{
		return std::make_unique<PropellerHat>(world, bodydef, pos);
	}
);