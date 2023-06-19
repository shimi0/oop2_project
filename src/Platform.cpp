#include "Platform.h"

Platform::Platform()
{
}


 void Platform::handleCollision(Player& player)
{
	player.handleCollision(*this);
}