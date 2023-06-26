#pragma once

#include "Gift.h"
#include "Player.h"

class JetPack : public Gift, public Movable
{
public:
	JetPack(std::unique_ptr<b2World>&, b2BodyDef&, const sf::Vector2f&);

	virtual void handleCollision(Player& obj) override;
	void step(const sf::Time& deltaTime)
	{
		
	}


	virtual void setPosition(const sf::Vector2f& pos)
	{
		if (!m_isInUse) return;
		sf::Vector2f positinon = { pos.x + m_playerGlobalBounds.width / 3, pos.y + 30 };
		m_objectBody->SetTransform(sfmlToBox2D(positinon), m_objectBody->GetAngle());
		m_sprite.setPosition(box2DToSFML(m_objectBody->GetPosition()));
	}

	virtual void attach(std::unique_ptr<b2World>& world, GameObject& obj)
	{
		if (!m_isInUse) return;
	}

private:
	void loadObject();

	sf::FloatRect m_playerGlobalBounds;
};