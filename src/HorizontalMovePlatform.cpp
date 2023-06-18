#include "HorizontalMovePlatform.h"

HorizontalMovePlatform::HorizontalMovePlatform(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	: GameObject(Resources::instance().animationData(Resources::BluePlatform), Direction::Stay, m_sprite), Platform(),
	Movable(Resources::instance().animationData(Resources::BluePlatform), Direction::Stay, m_sprite)
{
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(sfmlToBox2D(pos.x), sfmlToBox2D(pos.y));

	m_objectBody = world->CreateBody(&bodydef);

	loadObject();
	m_direction == Direction::Right;
}

//----------------------------------------

static auto registerIt = Factory<Movable>::instance().registerType(
	"HorizontalMovePlatform",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Movable>
	{
		return std::make_unique<HorizontalMovePlatform>(world, bodydef, pos);
	}
);

//----------------------------------------

void HorizontalMovePlatform::loadObject()
{

	b2PolygonShape playerBox;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale({ 2.f,2.f });

	//NOTICE: should be divided by 2. not by 6. but turns out to be too big. dont know why... 

	//Y should be m_sprite.getGlobalBounds().height / 2 for the full platform. curentlly it 0.01
	auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width / 6, 0.01f);
	playerBox.SetAsBox(box.x, box.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &playerBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 10.0f;
	m_objectBody->CreateFixture(&fixtureDef);

	m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));

	m_objectBody->SetGravityScale(0.0f);
}
