#pragma once

#include "Gift.h"
#include "Player.h"
#include "macros.h"

class JetPack : public Gift, public Movable
{
public:
	JetPack(std::unique_ptr<b2World>&, b2BodyDef&, const sf::Vector2f&);

	virtual void handleCollision(Player& obj) override;
	void step(const sf::Time& deltaTime)
	{
		
	}

	virtual void animate(const sf::Time& deltaTime)
	{
		if (m_clock.getElapsedTime().asSeconds() > JETPACK_TIME && m_isInUse)
		{
			m_isInUse = false;
			m_objectBody->SetEnabled(false);
			m_sprite.setColor(sf::Color::Transparent);
		}

		if (m_isInUse)
			m_animation.updateBasedOnTime(deltaTime);
	};

	virtual void setPosition(const sf::Vector2f& pos)
	{
		if (!m_isInUse) return;
		sf::Vector2f positinon = { pos.x + m_playerGlobalBounds.width / 3, pos.y + 30 };
		//curr only the sprtie moves to avoid multiple collisions
		//m_objectBody->SetTransform(sfmlToBox2D(positinon), m_objectBody->GetAngle());
		m_sprite.setPosition(positinon);
	}

	virtual void attach(std::unique_ptr<b2World>& world, GameObject& obj)
	{
		if (!m_isInUse) return;
	}

private:

	void loadObject();
	sf::Clock m_clock;
	sf::FloatRect m_playerGlobalBounds;
};