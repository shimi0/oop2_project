#include "JetPack.h"

JetPack::JetPack(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	:Gift(Resources::instance().animationData(Resources::JetPack), Direction::Stay, m_sprite),
	GameObject(Resources::instance().animationData(Resources::JetPack), Direction::Stay, m_sprite),
	Movable(Resources::instance().animationData(Resources::JetPack), Direction::Stay, m_sprite)
{
	defineBody(world, bodydef, pos);
	Gift::loadObject();
}

//----------------------------------------

void JetPack::handleCollision(Player& obj)
{
	if (!obj.isAllowedToUseGift())
		return;
	m_animation.direction(Direction::Left);
	m_isInUse = true;
	m_clock.restart();
	obj.handleCollision(*this);
	m_playerGlobalBounds = obj.getGlobalBounds();
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