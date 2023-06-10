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
	m_player.loadObject(world, bodyDef);


	//temp ground-------------------------------------------------------------
	// Create the ground body

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(sfmlToBox2D(200.f), sfmlToBox2D(1900.f) ); // Position the ground at the bottom of the window
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Create the ground shape
	b2PolygonShape groundShape;
	groundShape.SetAsBox(sfmlToBox2D(640.f * 2), sfmlToBox2D(0.01f)); // Set the dimensions of the ground shape
	
	// Create the ground fixture
	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &groundShape;
	groundFixtureDef.friction = 0.01f;
	groundFixtureDef.density = 1.0f;
	groundBody->CreateFixture(&groundFixtureDef);

	//create 1 platform - temp

	m_platform.loadObject(world, bodyDef);

	while (m_window.isOpen())
	{
		world->Step(1.0f / 60.0f, 10, 5);
		m_window.clear(sf::Color::Black);
		m_board.draw();
		m_player.setPosition({ 0,0 });	//temp - make it fall
		m_player.draw(m_window);
		m_platform.draw(m_window);
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
