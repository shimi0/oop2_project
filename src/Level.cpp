#include "Level.h"

Level::Level(sf::RenderWindow& window)
	:m_window(window), m_board(window)
{
	m_window.create(sf::VideoMode(640 * 2, 1024 * 2), "Doodle Jump"); //exception?
	m_window.setFramerateLimit(60);
}

//------------------------------

void Level::run()
{
	m_player.loadPlayer();
	while (m_window.isOpen())
	{
		m_window.clear(sf::Color::Black);
		m_board.draw();
		m_window.display();
		sf::Event event;
		while (m_window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				m_window.close();


	}
	
}
