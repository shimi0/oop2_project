#pragma once

#include "Player.h"
#include "GameObject.h"

class Player;

class Platform : virtual public GameObject
{
public:
	Platform();
	virtual ~Platform() = 0 {}

	virtual void handleCollision(Player& player) override;

	
protected:
	void loadObject();

private:

};

