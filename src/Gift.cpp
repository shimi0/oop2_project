#include "Gift.h"

Gift::Gift(const AnimationData& data, Direction dir, sf::Sprite& sprite)
	:GameObject(data, dir, sprite)
{}

//----------------------------------------------------

void Gift::loadObject()
{
	b2PolygonShape playerBox;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale({ 2.f,2.f });

	auto box = sfmlToBox2D(m_sprite.getGlobalBounds().width / 6, m_sprite.getGlobalBounds().height / 4);
	playerBox.SetAsBox(box.x, box.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &playerBox;
	m_objectBody->CreateFixture(&fixtureDef);

	m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));
}
