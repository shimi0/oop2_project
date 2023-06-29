#pragma once

#include "Gift.h"
#include "Player.h"
#include "macros.h"

class PropellerHat : public Gift, public Movable
{
public:
	PropellerHat(std::unique_ptr<b2World>&, b2BodyDef&, const sf::Vector2f&);

	virtual void handleCollision(Player& obj) override;
	void step(const sf::Time& deltaTime) {}

	virtual void animate(const sf::Time& deltaTime)
	{
		if (m_clock.getElapsedTime().asSeconds() > PROPELLER_HAT_TIME && m_isInUse)
		{
			m_isInUse = false;
			m_objectBody->SetEnabled(false);
			m_sprite.setColor(sf::Color::Transparent);
		}

		if(m_isInUse)
			m_animation.updateBasedOnTime(deltaTime);
	};


	virtual void setPosition(const sf::Vector2f& pos)
	{
		if (!m_isInUse) return;
		sf::Vector2f positinon = { pos.x, pos.y - m_playerGlobalBounds.height / 3.2f };
		m_objectBody->SetTransform(sfmlToBox2D(positinon), m_objectBody->GetAngle());
		m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));
	}

private:

	sf::FloatRect m_playerGlobalBounds;
	sf::Clock m_clock;
};