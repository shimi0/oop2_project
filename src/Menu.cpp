#include "Menu.h"

Menu::Menu(sf::RenderWindow& window)
	:m_window(window)
{
}

void Menu::run()
{
	m_window.setTitle("Doodle Jump - Menu");
}
