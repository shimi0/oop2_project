#include "FireMonster.h"

FireMonster::FireMonster(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	:Unmovable(Resources::instance().animationData(Resources::FireMonster), Direction::Stay, m_sprite),
	GameObject(Resources::instance().animationData(Resources::FireMonster), Direction::Stay, m_sprite)
{
	bodydef.type = b2_staticBody;
	bodydef.position.Set(sfmlToBox2D(pos.x), sfmlToBox2D(pos.y));

	m_objectBody = world->CreateBody(&bodydef);

	loadObject();
}

//----------------------------------------

static auto registerIt = Factory<Unmovable>::instance().registerType(
	"FireMonster",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Unmovable>
	{
		return std::make_unique<FireMonster>(world, bodydef, pos);
	}
);


//-------------------------------------------

void FireMonster::loadObject()
{

	b2PolygonShape playerBox;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale({ 2.f,2.f });
	auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width / 5.0f, m_sprite.getGlobalBounds().height / 5.f);
	playerBox.SetAsBox(box.x, box.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &playerBox;
	m_objectBody->CreateFixture(&fixtureDef);
	m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));

	m_objectBody->SetGravityScale(0.0f);
}

//-----------------------------------------------------

void FireMonster::handleCollision(Player& obj)
{
	obj.handleCollision(*this);
}
