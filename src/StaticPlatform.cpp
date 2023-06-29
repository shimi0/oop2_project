#include "StaticPlatform.h"

StaticPlatform::StaticPlatform(std::unique_ptr<b2World>&world, b2BodyDef & bodydef, const sf::Vector2f& pos)
	: GameObject(Resources::instance().animationData(Resources::GreenPlatform), Direction::Stay, m_sprite), Platform(),
	Unmovable(Resources::instance().animationData(Resources::GreenPlatform), Direction::Stay, m_sprite)
{
	defineBody(world, bodydef, pos);
	Platform::loadObject();
}

//----------------------------------------

bool StaticPlatform::isMovable() const
{
	return false;
}

//----------------------------------------

static auto registerIt = Factory<Platform>::instance().registerType(
	"StaticPlatform",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Platform>
	{
		return std::make_unique<StaticPlatform>(world, bodydef, pos);
	}
);