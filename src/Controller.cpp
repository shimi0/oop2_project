#include "Controller.h"

Controller::Controller()
	:m_window(sf::VideoMode(0,0), "")
{}
//---------------------------------------------

void Controller::run()
{
	m_window.create(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "Doodle Jump"); //exception?
	setIcon();
	srand(time(NULL));
	m_window.setFramerateLimit(60);

	auto& resources = Resources::instance();
	const std::multimap <int, std::string>& m_records = {};
	
	while (true) {
		Menu(m_window, m_records).run();

		Game(m_window).run();
	}
}

//---------------------------------------------

void Controller::setIcon()
{
	sf::Image icon;
	if (!icon.loadFromFile("Icon.png"))
		throw std::runtime_error("Unable to load Icon");
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
