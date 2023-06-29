#include "StaticPlatform.h"

StaticPlatform::StaticPlatform(std::unique_ptr<b2World>&world, b2BodyDef & bodydef, const sf::Vector2f& pos)
	: GameObject(Resources::instance().animationData(Resources::GreenPlatform), Direction::Stay, m_sprite), Platform(),
	Unmovable(Resources::instance().animationData(Resources::GreenPlatform), Direction::Stay, m_sprite)
{
	bodydef.type = b2_staticBody;
	bodydef.position.Set(sfmlToBox2D(pos.x), sfmlToBox2D(pos.y));

	m_objectBody = world->CreateBody(&bodydef);

	Platform::loadObject();
}

//----------------------------------------

static auto registerIt = Factory<Platform>::instance().registerType(
	"StaticPlatform",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Platform>
	{
		return std::make_unique<StaticPlatform>(world, bodydef, pos);
	}
);