#pragma once

#include "Movable.h"
#include "Unmovable.h"
#include "SFML/Audio.hpp"
#include "macros.h"

//a bullet. curently shooting only up

class Bullet : public Movable
{
public:

	Bullet(const sf::Vector2f& position);

	void loadObject(std::unique_ptr<b2World>&, b2BodyDef&) override;

	bool isMovingUp() const;
	virtual void handleCollision(GameObject& obj) override;
	virtual void step(const sf::Time&) override;
	void shoot();
	bool hasFallen() const;

private:

	sf::Sound m_sound;
	sf::Vector2f m_position;

	bool m_hasBeenshot = false;

	//falls after an amount of time
	bool m_hasFallen = false;
	sf::Clock m_timeSinceShot;
};