#pragma once

#include <iostream>

#include "GameObject.h"

class Platform : virtual public GameObject
{
public:
	Platform();
	virtual ~Platform() = 0 {}

	virtual void handleCollision(Player& obj)
	{
		std::cout << "Sdaa";
	}
protected:


private:

};

