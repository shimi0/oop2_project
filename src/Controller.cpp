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

	//auto& resources = Resources::instance();
	auto scores = ScoresManager();

//	scores.addRecord(m_window, 500);
	while (true) 
	{
		auto menu = Menu(m_window);
		menu.run();

		switch (menu.getPressedButton())
		{
			case ButtonIndexMenu::SCORESBUT: ScoresBoard(m_window, scores.getRecords()).run(); break;
			case ButtonIndexMenu::PLAYBUT:	Game(m_window).run(scores); break;
			default: break;
		}
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
