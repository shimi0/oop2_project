#include "Controller.h"

Controller::Controller()
	:m_window(sf::VideoMode(0,0), "")
{
}

//---------------------------------------------

void Controller::run()
{
	auto& resources = Resources::instance();

	Game(m_window).run();
}
