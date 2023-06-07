#pragma once

#include "SFML/Graphics.hpp"

class Menu
{
public:

	Menu(sf::RenderWindow& window);

	void run();


private:

	sf::RenderWindow& m_window;
};