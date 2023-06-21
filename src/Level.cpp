#include "Level.h"

Level::Level(sf::RenderWindow& window)
	:m_window(window), m_board(window)
{
	m_window.create(sf::VideoMode(WIN_SIZE_X, WIN_SIZE_Y), "Doodle Jump"); //exception?
	m_window.setFramerateLimit(60);

	// Define the gravity vector
	b2Vec2 gravity(0.0f, 15.0f);
	m_world = std::make_unique<b2World>(gravity);
}

//------------------------------

void Level::run()
{
	//collision detection
	auto contactListener = ContactListener(m_player, m_unmovableObjVec, m_movableObjVec, m_platformVec);
	m_world->SetContactListener(&contactListener);

	//auto bodyDef = b2BodyDef();
	m_player.loadObject(m_world, m_bodyDef);

	auto clock = sf::Clock();
	auto deltaTime = clock.restart();

	sf::View gameView;

	gameView.setSize(sf::Vector2f(m_window.getSize()));
	gameView.setCenter(sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2));

	while (m_window.isOpen())
	{
		deltaTime = clock.restart();
		m_world->Step(1.0f / 60.0f, 10, 5);
		adjustView(gameView);
		drawGraphics();
		if(!m_player.isDying())
			m_player.matchSptitePosToBody();
		m_player.updateAnimation();
		for (auto& item : m_movableObjVec)
			item->step(deltaTime);
		processEvent(deltaTime);

		
		if (m_player.isDying())
			m_player.playDyingBehavior();
		if (!m_player.isAlive())
		{ 
			m_player.starsAnimation(deltaTime);
			//m_window.close();
		}
			

	}
}

//-------------------------------------------

void Level::adjustView(sf::View& gameView)
{
	sf::FloatRect viewPort = gameView.getViewport();

	sf::Vector2u windowSize = m_window.getSize();

	//calc global coordinates view
	sf::Vector2f topLeft = m_window.mapPixelToCoords(sf::Vector2i(viewPort.left * windowSize.x, viewPort.top * windowSize.y));

	float PlayerBasePos = m_player.getBasePosition().y;

	if (!m_player.isAlive())
	{
		static int a = 0;
		a++;
		if (a* 18 < WIN_SIZE_Y*2 )	//TO_DO: he update is +18. so it should be until a*18 > WIN_SIZE
		{
			gameView.move(0, 18);
			//	gameView.setCenter(gameView.getCenter().x, gameView.getCenter().y + 17);
				//gameView.setCenter(gameView.getCenter().x, gameView.getCenter().y + 20);
			m_board.updateBGPos(sf::Vector2f(topLeft.x, topLeft.y + 18));
		}
	}
	else if (WIN_SIZE_Y - 350 + topLeft.y > PlayerBasePos)	//set 2000 and 200, 10 as global macro 
	{
		gameView.setCenter(gameView.getCenter().x, gameView.getCenter().y + ((PlayerBasePos - WIN_SIZE_Y - topLeft.y + 350) / 10));
		m_board.updateBGPos(sf::Vector2f(topLeft.x, topLeft.y + ((PlayerBasePos - WIN_SIZE_Y - topLeft.y + 350) / 10)));
	}
	m_window.setView(gameView);
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

	for (auto& platform : m_platformVec)
	{
		//if he died wo dont wanna see the platform while falling down
		if(platform->getPosition().y < m_player.getBasePosition().y + 650)	//650 shold ne the size under the base platform * 2 or *3
			platform->draw(m_window);
	}
	for (auto& staticObj : m_unmovableObjVec)
		staticObj->draw(m_window);
	for (auto& movableObj : m_movableObjVec)
		movableObj->draw(m_window);
	
	m_player.draw(m_window);
	if (!m_player.isAlive())
		m_player.drawStars(m_window);
	m_window.display();
}

//--------------------------------------------