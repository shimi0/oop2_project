#include "SpringGift.h"

SpringGift::SpringGift(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	:Gift(Resources::instance().animationData(Resources::SpringGift), Direction::Down, m_sprite),
	Unmovable(Resources::instance().animationData(Resources::SpringGift), Direction::Down, m_sprite),
	GameObject(Resources::instance().animationData(Resources::SpringGift), Direction::Down, m_sprite)
{
	bodydef.type = b2_staticBody;
	bodydef.position.Set(sfmlToBox2D(pos.x), sfmlToBox2D(pos.y));

	m_objectBody = world->CreateBody(&bodydef);

	Gift::loadObject();
}

//----------------------------------------

void SpringGift::handleCollision(Player& obj)
{
	if (!obj.isAllowedToUseGift()) return;

	m_animation.direction(Direction::Up);
	obj.handleCollision(*this);
}

//----------------------------------------

static auto registerIt = Factory<Unmovable>::instance().registerType(
	"SpringGift",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Unmovable>
	{
		return std::make_unique<SpringGift>(world, bodydef, pos);
	}
);