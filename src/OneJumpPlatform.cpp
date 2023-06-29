#include "OneJumpPlatform.h"

OneJumpPlatform::OneJumpPlatform(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	: GameObject(Resources::instance().animationData(Resources::OneJumpPlatform), Direction::Stay, m_sprite), Platform(),
	Unmovable(Resources::instance().animationData(Resources::OneJumpPlatform), Direction::Stay, m_sprite)
{
	defineBody(world, bodydef, pos);
	Platform::loadObject();
}

//----------------------------------------

bool OneJumpPlatform::isMovable() const
{
	return false;
}

//----------------------------------------

void OneJumpPlatform::animate(const sf::Time& deltaTime)
{
	if (m_hasBeenUsed)
	{
		m_sprite.setColor(sf::Color::Transparent);
		m_objectBody->SetEnabled(false);
	}
}

//----------------------------------------

static auto registerIt = Factory<Platform>::instance().registerType(
	"OneJumpPlatform",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Platform>
	{
		return std::make_unique<OneJumpPlatform>(world, bodydef, pos);
	}
);