#pragma once

#include <iostream>
#include "Game.h"
#include "Menu.h"
#include "Resources.h"
#include "ScoresBoard.h"
#include "ScoresManager.h"
#include "SFML/Graphics.hpp"

//runs the full program

class Controller
{
public:
	Controller();

	void run();

private:

	//the window icon
	void setIcon();

	sf::RenderWindow m_window;
};