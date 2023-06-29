#pragma once

#include "Gift.h"
#include "Unmovable.h"
#include "Player.h"

class SpringGift : public Gift, public Unmovable
{
public:
	SpringGift(std::unique_ptr<b2World>&, b2BodyDef&, const sf::Vector2f&);

	virtual void handleCollision(Player& obj) override;

private:

};