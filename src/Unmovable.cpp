#include "Unmovable.h"

Unmovable::Unmovable(const AnimationData& data, Direction dir, sf::Sprite& sprite)
	:GameObject(data, dir, sprite)
{
}

//-----------------------------------------------

void Unmovable::defineBody(std::unique_ptr<b2World>& world, b2BodyDef& bodydef, const sf::Vector2f& pos)
{
	bodydef.type = b2_staticBody;
	bodydef.position.Set(sfmlToBox2D(pos.x), sfmlToBox2D(pos.y));
	m_objectBody = world->CreateBody(&bodydef);
}