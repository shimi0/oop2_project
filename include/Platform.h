#pragma once

#include <iostream>
#include "Player.h"
#include "GameObject.h"

class Player;

class Platform : virtual public GameObject
{
public:
	Platform();
	virtual ~Platform() = 0 {}

	virtual void handleCollision(Player& player) override;
	//{
	//	player.jump();
	//	//player.handleCollision(*this);
	//}

protected:


private:

};

