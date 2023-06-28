#pragma once

#include "Movable.h"
#include "Unmovable.h"

class Bullet : public Movable
{
public:
	Bullet(const sf::Vector2f& position);

	bool isMovingUp() const;

	void loadObject(std::unique_ptr<b2World>& world, b2BodyDef& bodydef) override;
	virtual void handleCollision(GameObject& obj);

	virtual void step(const sf::Time& deltaTime)
	{
		matchSptitePosToBody();
		if (m_hasBeenUsed)
			if (m_timeSinceShot.getElapsedTime().asSeconds() > 4.0f)
				m_hasFallen = true;

	
	}
	void shoot()
	{
		if (!m_hasBeenUsed)
			m_hasBeenUsed = true;
		else
			return;
		m_timeSinceShot.restart();
		float sideAngle = 0;
		int num = rand() % 7;
		switch (num)
		{
			case 0:	sideAngle = 0;				break;
			case 1:	sideAngle =  0.01 * 3;			break;
			case 2:	sideAngle =  0.02 * 3;			break;
			case 3:	sideAngle = -0.01 * 3;			break;
			case 4:	sideAngle = -0.02 * 3;			break;
			case 5:	sideAngle =  0.03 * 3;			break;
			case 6:	sideAngle = -0.03 * 3;			break;
			default: break;
		}
		m_objectBody->ApplyLinearImpulseToCenter({ sideAngle,-2.4f }, true);
	}

	bool hasFallen() const
	{
		return m_hasFallen;
	}
private:
	sf::Vector2f m_position;

	bool m_hasBeenUsed = false;
	bool m_hasFallen = false;	//change name
	sf::Clock m_timeSinceShot;
};