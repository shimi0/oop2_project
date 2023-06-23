#include "Controller.h"

Controller::Controller()
	:m_window(sf::VideoMode(0,0), "")
{
}

//---------------------------------------------

void Controller::run()
{
	m_window.create(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "Doodle Jump"); //exception?

	m_window.setFramerateLimit(60);

	auto& resources = Resources::instance();

	Game(m_window).run();
	Menu(m_window).run();
}
