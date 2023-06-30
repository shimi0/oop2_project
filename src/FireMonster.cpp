#include "FireMonster.h"

FireMonster::FireMonster(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	:Unmovable(Resources::instance().animationData(Resources::FireMonster), Direction::Stay, m_sprite),
	GameObject(Resources::instance().animationData(Resources::FireMonster), Direction::Stay, m_sprite)
{
	defineBody(world, bodydef, pos);

	Enemy::loadObject();
	m_scoreWorth = 5000;
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
