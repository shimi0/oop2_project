#include "Movable.h"

Movable::Movable(const AnimationData& data, Direction dir, sf::Sprite& sprite)
	:GameObject(data, dir, sprite)
{}

//-------------------------------------------

void Movable::matchSptitePosToBody()
{
	m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));
}
