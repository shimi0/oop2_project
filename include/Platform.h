#pragma once

#include "Player.h"
#include "GameObject.h"

//a base class for a game platform

class Player;

class Platform : virtual public GameObject
{
public:
	Platform();
	virtual ~Platform() = 0 {}

	virtual void handleCollision(Player& player) override;
	virtual void step(const sf::Time& deltaTime) {};
	virtual bool isMovable() const = 0;
protected:
	void loadObject();
	bool m_hasBeenUsed = false;
private:

	
};

