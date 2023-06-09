#include "GameObject.h"

GameObject::GameObject(const AnimationData& data, Direction dir, sf::Sprite& sprite)
	:m_animation(data, dir, sprite)
{
}


//----------------------------------

void GameObject::draw(sf::RenderWindow& window) 
{
	//m_sprite.setPosition(50, 50);
	window.draw(m_sprite);
}
