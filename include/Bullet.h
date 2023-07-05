#pragma once

#include "Movable.h"
#include "Unmovable.h"
#include "SFML/Audio.hpp"
#include "macros.h"

class Bullet : public Movable
{
public:

	Bullet(const sf::Vector2f& position);

	bool isMovingUp() const;

	void loadObject(std::unique_ptr<b2World>&, b2BodyDef&) override;
	virtual void handleCollision(GameObject& obj);

	virtual void step(const sf::Time&) override;
	void shoot();

	bool hasFallen() const;

private:
	sf::Sound m_sound;
	sf::Vector2f m_position;

	bool m_hasBeenshot = false;
	bool m_hasFallen = false;
	sf::Clock m_timeSinceShot;
};