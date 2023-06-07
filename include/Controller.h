#pragma once

#include "Game.h"
#include "Menu.h"
#include "Resources.h"
#include "SFML/Graphics.hpp"

class Controller
{

public:
	Controller();
	

	void run();



private:

	sf::RenderWindow m_window;
};