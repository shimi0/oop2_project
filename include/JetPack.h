#pragma once

#include "Gift.h"
#include "Player.h"
#include "macros.h"

//a gift. takes the player up for a few seconds. moving fast

class JetPack : public Gift, public Movable
{
public:

	JetPack(std::unique_ptr<b2World>&, b2BodyDef&, const sf::Vector2f&);

	virtual void handleCollision(Player& obj) override;
	void step(const sf::Time& deltaTime) {}

	virtual void animate(const sf::Time& deltaTime) override;
	virtual void setPosition(const sf::Vector2f& pos) override;

private:

	sf::Sound m_sound;
	sf::Clock m_clock;
	sf::FloatRect m_playerGlobalBounds;
};