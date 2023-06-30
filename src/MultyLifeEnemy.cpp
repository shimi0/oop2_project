
#include "MultyLifeEnemy.h"

MultyLifeEnemy::MultyLifeEnemy(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	:Unmovable(Resources::instance().animationData(Resources::MultyLifeEnemy), Direction::Down, m_sprite),
	GameObject(Resources::instance().animationData(Resources::MultyLifeEnemy), Direction::Down, m_sprite)
{
	defineBody(world, bodydef, pos);
	m_lives = 2;
	Enemy::loadObject();
}

//----------------------------------------

static auto registerIt = Factory<Unmovable>::instance().registerType(
	"MultyLifeEnemy",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Unmovable>
	{
		return std::make_unique<MultyLifeEnemy>(world, bodydef, pos);
	}
);

//-----------------------------------------------------

void MultyLifeEnemy::handleCollision(Player& obj)
{
	obj.handleCollision(*this);
}

//-----------------------------------------------------

void MultyLifeEnemy::handleCollision(Bullet& obj)
{
	Enemy::handleCollision(obj);
	m_animation.direction(Direction::Up);
}
