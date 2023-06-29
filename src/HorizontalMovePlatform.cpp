#include "HorizontalMovePlatform.h"

HorizontalMovePlatform::HorizontalMovePlatform(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	: GameObject(Resources::instance().animationData(Resources::BluePlatform), Direction::Stay, m_sprite), Platform(),
	  Movable(Resources::instance().animationData(Resources::BluePlatform), Direction::Stay, m_sprite)
{
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(sfmlToBox2D(pos.x), sfmlToBox2D(pos.y));

	m_objectBody = world->CreateBody(&bodydef);

	Platform::loadObject();
	m_direction == Direction::Right;
}

//----------------------------------------

void HorizontalMovePlatform::step(const sf::Time& deltaTime)
{
	//m_direction = Direction::Right;

	if (box2DToSFML(m_objectBody->GetPosition()).x < 150.f)
		m_direction = Direction::Right;

	if (box2DToSFML(m_objectBody->GetPosition()).x > (WIN_SIZE_X - 150))
		m_direction = Direction::Left;
	float desiredVelocity = 0.0f;
	switch (m_direction)
	{
		case Direction::Right: desiredVelocity = 3.0f;       break;
		case Direction::Left:  desiredVelocity = -3.0f;      break;
		case Direction::Stay:  desiredVelocity = 0.0f;       break;
		default:                                             break;
	}
	updatePositionX(desiredVelocity);
	matchSptitePosToBody();
}

//----------------------------------------

static auto registerIt = Factory<Platform>::instance().registerType(
	"HorizontalMovePlatform",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Platform>
	{
		return std::make_unique<HorizontalMovePlatform>(world, bodydef, pos);
	}
);