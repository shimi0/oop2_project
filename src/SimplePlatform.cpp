#include "SimplePlatform.h"

SimplePlatform::SimplePlatform(std::unique_ptr<b2World>&world, b2BodyDef & bodydef, const sf::Vector2f& pos)
	: GameObject(Resources::instance().animationData(Resources::GreenPlatform), Direction::Stay, m_sprite), Platform(),
	Unmovable(Resources::instance().animationData(Resources::GreenPlatform), Direction::Stay, m_sprite)
{
	bodydef.type = b2_staticBody;
	bodydef.position.Set(sfmlToBox2D(pos.x), sfmlToBox2D(pos.y));

	m_objectBody = world->CreateBody(&bodydef);

	loadObject();
}

//----------------------------------------

void SimplePlatform::loadObject()
{

	b2PolygonShape playerBox;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale({ 2.f,2.f });

	//NOTICE: should be divided by 2. not by 6. but turns out to be to big. dont know why... 
	auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width / 6, m_sprite.getGlobalBounds().height / 2);
	playerBox.SetAsBox(box.x, box.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &playerBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 10.0f;
	m_objectBody->CreateFixture(&fixtureDef);

	m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));

	
}
