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
	// Define the gravity vector
	b2Vec2 gravity(0.0f, 10.0f);
	auto world = std::make_unique<b2World>(gravity);

	auto bodyDef = b2BodyDef();
	// Define the gravity vector
	m_player.loadPlayer(world, bodyDef);


	while (m_window.isOpen())
	{
		world->Step(1.0f / 60.0f, 8, 3);
		m_window.clear(sf::Color::Black);
		m_board.draw();
		m_player.draw(m_window);
		m_window.display();
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();

			if (event.type == sf::Event::KeyReleased)
				m_player.processKeyInput(event);
		}


	}
	
}
