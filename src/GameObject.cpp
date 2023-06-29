#include "GameObject.h"

GameObject::GameObject(const AnimationData& data, Direction dir, sf::Sprite& sprite)
	:m_animation(data, dir, sprite)
{}

//----------------------------------

void GameObject::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

//----------------------------------

bool GameObject::isSameBody(const b2Body* other) const
{
	return m_objectBody == other;
}

//----------------------------------

sf::Vector2f GameObject::getPosition() const
{
	return m_sprite.getPosition();
}

//----------------------------------

sf::FloatRect GameObject::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

//----------------------------------

void GameObject::animate(const sf::Time& deltaTime)
{
	m_animation.updateBasedOnTime(deltaTime);
}
