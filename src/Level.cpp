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
	b2Vec2 gravity(0.0f, 15.0f);
	auto world = std::make_unique<b2World>(gravity);
	
	//collision detection
	auto contactListener = ContactListener(m_player, m_simplePlatformsVec);
	world->SetContactListener(&contactListener);

	auto bodyDef = b2BodyDef();
	m_player.loadObject(world, bodyDef);

	auto clock = sf::Clock();
	auto deltaTime = clock.restart();

	auto pos = sf::Vector2f(600.f, 1024.f * 2);
	m_simplePlatformsVec.emplace_back(world, bodyDef, pos);

	pos = sf::Vector2f(800.f, 1024.f * 2 - 300);
	m_simplePlatformsVec.emplace_back(world, bodyDef, pos);

	pos = sf::Vector2f(400, 1024.f * 2 - 500);
	m_simplePlatformsVec.emplace_back(world, bodyDef, pos);
	//m_platform.loadObject(world, bodyDef);

	while (m_window.isOpen())
	{
		deltaTime = clock.restart();
		world->Step(1.0f / 60.0f, 10, 5);
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
		platform.draw(m_window);
	m_window.display();
}
