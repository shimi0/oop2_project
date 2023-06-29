#include "FireMonster.h"

FireMonster::FireMonster(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	:Unmovable(Resources::instance().animationData(Resources::FireMonster), Direction::Stay, m_sprite),
	GameObject(Resources::instance().animationData(Resources::FireMonster), Direction::Stay, m_sprite)
{
	bodydef.type = b2_staticBody;
	bodydef.position.Set(sfmlToBox2D(pos.x), sfmlToBox2D(pos.y));

	m_objectBody = world->CreateBody(&bodydef);

	Enemy::loadObject();
}

//----------------------------------------

static auto registerIt = Factory<Unmovable>::instance().registerType(
	"FireMonster",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Unmovable>
	{
		return std::make_unique<FireMonster>(world, bodydef, pos);
	}
);

//-----------------------------------------------------

void FireMonster::handleCollision(Player& obj)
{
	obj.handleCollision(*this);
}
