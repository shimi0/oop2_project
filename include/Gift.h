#pragma once

#include "Animation.h"
#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Factory.h"
#include "Unmovable.h"
#include "GameObject.h"

class Gift : virtual public GameObject
{
public:
	Gift(const AnimationData& data, Direction dir, sf::Sprite& sprite);

	void attachTo(const sf::Vector2f& position)
	{
		if (!m_isInUse) return;
		m_objectBody->SetTransform(sfmlToBox2D(position), m_objectBody->GetAngle());
		m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));
	}


protected:

	bool m_hasBeenUsed = false;
	bool m_isInUse = false;
private:

	

};