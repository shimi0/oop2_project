#include "ExplodingPlatform.h"

ExplodingPlatform::ExplodingPlatform(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	: GameObject(Resources::instance().animationData(Resources::ExplodingPlatform), Direction::Stay, m_sprite), Platform(),
	Unmovable(Resources::instance().animationData(Resources::ExplodingPlatform), Direction::Stay, m_sprite)
{
	bodydef.type = b2_staticBody;
	bodydef.position.Set(sfmlToBox2D(pos.x), sfmlToBox2D(pos.y));

	m_objectBody = world->CreateBody(&bodydef);

	Platform::loadObject();
}

//----------------------------------------

void ExplodingPlatform::animate(const sf::Time& deltaTime)
{
	if (m_animation.isEndOfAnimation())
	{
		m_objectBody->SetEnabled(false);
		m_sprite.setColor(sf::Color::Transparent);
		return;
	}
	m_animation.updateBasedOnTime(deltaTime);
}

//----------------------------------------

static auto registerIt = Factory<Platform>::instance().registerType(
	"ExplodingPlatform",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Platform>
	{
		return std::make_unique<ExplodingPlatform>(world, bodydef, pos);
	}
);