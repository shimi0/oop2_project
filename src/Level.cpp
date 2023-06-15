#include "Level.h"

Level::Level(sf::RenderWindow& window)
	:m_window(window), m_board(window)
{
	m_window.create(sf::VideoMode(640 * 2, 1024 * 2), "Doodle Jump"); //exception?
	m_window.setFramerateLimit(60);

	// Define the gravity vector
	b2Vec2 gravity(0.0f, 15.0f);
	m_world = std::make_unique<b2World>(gravity);
}

//------------------------------

void Level::run()
{
	//collision detection
	auto contactListener = ContactListener(m_player, m_simplePlatformsVec);
	m_world->SetContactListener(&contactListener);

	//auto bodyDef = b2BodyDef();
	m_player.loadObject(m_world, m_bodyDef);

	auto clock = sf::Clock();
	auto deltaTime = clock.restart();

	while (m_window.isOpen())
	{
		deltaTime = clock.restart();
		m_world->Step(1.0f / 60.0f, 10, 5);
		drawGraphics();
		m_player.matchSptitePosToBody();
		m_player.updateAnimation();
		processEvent(deltaTime);
	}
}

//-------------------------------------------

void Level::processEvent(const sf::Time& deltaTime)
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
		m_player.processKeyInput(event, deltaTime);
	}
}

//-------------------------------------------

void Level::drawGraphics()
{
	m_window.clear(sf::Color::Black);
	m_board.draw();
	m_player.draw(m_window);
//	m_platform.draw(m_window);
	for (auto& platform : m_simplePlatformsVec)
		platform->draw(m_window);
	m_window.display();
}
