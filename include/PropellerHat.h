#pragma once

#include "Gift.h"
#include "Player.h"
#include "macros.h"

//a gift. takes the player up for a few secpnds. moving slow.

class PropellerHat : public Gift, public Movable
{
public:

	PropellerHat(std::unique_ptr<b2World>&, b2BodyDef&, const sf::Vector2f&);

	virtual void handleCollision(Player& obj) override;
	void step(const sf::Time& deltaTime) {}

	virtual void animate(const sf::Time& deltaTime) override;
	virtual void setPosition(const sf::Vector2f& pos) override;

private:

	sf::Sound m_sound;

	//in use to place the graphic in the right position
	sf::FloatRect m_playerGlobalBounds;
	sf::Clock m_clock;
};