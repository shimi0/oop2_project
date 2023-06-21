#include "BlackHoleEnemy.h"

BlackHoleEnemy::BlackHoleEnemy(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
	:Unmovable(Resources::instance().animationData(Resources::BlackHoleEnemy), Direction::Stay, m_sprite),
	GameObject(Resources::instance().animationData(Resources::BlackHoleEnemy), Direction::Stay, m_sprite)
{
	bodydef.type = b2_staticBody;
	bodydef.position.Set(sfmlToBox2D(pos.x), sfmlToBox2D(pos.y));

	m_objectBody = world->CreateBody(&bodydef);

	loadObject();
}


//----------------------------------------

static auto registerIt = Factory<Unmovable>::instance().registerType(
	"BlackHoleEnemy",
	[](std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos) -> std::unique_ptr<Unmovable>
	{
		return std::make_unique<BlackHoleEnemy>(world, bodydef, pos);
	}
);

//-------------------------------------------

void BlackHoleEnemy::loadObject()
{
	b2PolygonShape playerBox;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale({ 1.3f, 1.3f });

	//NOTICE: should be divided by 2. not by 6. but turns out to be too big. dont know why... 

	//Y should be m_sprite.getGlobalBounds().height / 2 for the full platform. curentlly it 0.01
	auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width / 20.0f, m_sprite.getGlobalBounds().height / 20.f);
	playerBox.SetAsBox(box.x, box.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &playerBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 10.0f;
	m_objectBody->CreateFixture(&fixtureDef);
	m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));
}

//----------------------------------------

void BlackHoleEnemy::handleCollision(Player& obj)
{
	std::cout << "d";
	obj.handleCollision(*this);
}
