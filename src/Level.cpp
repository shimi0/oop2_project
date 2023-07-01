#include "Level.h"

Level::Level(sf::RenderWindow& window, Board& board)
	:m_window(window),m_board(board)
{
	// Define the gravity vector
	b2Vec2 gravity(0.0f, 15.0f);
	m_world = std::make_unique<b2World>(gravity);
}

//-------------------------------------------

void Level::updateScore()
{
	int score = 0;
	score += m_player.getScore();
	for (auto& item : m_movableObjVec)
		score += item->getScoreWorth();

	for (auto& item : m_unmovableObjVec)
		score += item->getScoreWorth();

	
	m_board.updateScore( score);
}

//-------------------------------------------

void Level::run()
{
	//collision detection
	auto contactListener = ContactListener(m_player, m_unmovableObjVec, m_movableObjVec, m_platformVec, m_bullers);
	auto gameView = ViewManager();
	auto clock = sf::Clock();
	auto deltaTime = clock.restart();
	loadLevelData(contactListener);

	while (m_lvlRunnig)
	{
		deltaTime = clock.restart();
		adjustView(gameView);
		stepWorld(deltaTime);
		drawGraphics();
		processEvent(deltaTime);
		isPlayerInWindow();
		animateObjects(deltaTime);
		handleBulletShooting();
		updateScore();

		//reduce high power usage --
		sf::sleep(sf::milliseconds(10));
	}
}

//-------------------------------------------

float Level::getGlobalCordsY()
{
	sf::FloatRect viewPort = m_window.getView().getViewport();
	sf::Vector2f topLeft = m_window.mapPixelToCoords(sf::Vector2i(viewPort.left * WIN_SIZE_X, viewPort.top * WIN_SIZE_Y));
	return topLeft.y;
}

//-------------------------------------------

void Level::stepWorld(const sf::Time& deltaTime)
{
	if (!m_board.isPaused())
		m_world->Step(1.0f / 60.0f, 10, 5);

	for (auto& item : m_movableObjVec)
		item->step(deltaTime);

	//not so pretty but instead od using 2 different vectors(moving platform and unmonable) 
	//step is only working for movable platforms so should be safe to use
	for (auto& item : m_platformVec)
		if(item->isMovable())
			item->step(deltaTime);

	//there  are some objects that should get the players cur position.
	for (auto& obj : m_movableObjVec)
	{
		obj->setPosition(m_player.getPosition());
	}

	for (auto& bullet : m_bullers)
		bullet->step(deltaTime);
}

//-------------------------------------------

void Level::animateObjects(const sf::Time& deltaTime)
{
	if (m_board.isPaused()) return;

	m_player.animate(deltaTime);
	//dont animate before seen in the window(some objects only animate once!
	auto globalChordsY = getGlobalCordsY();
	for (auto& platform : m_platformVec)
		if (platform->getPosition().y < globalChordsY + WIN_SIZE_Y && platform->getPosition().y > globalChordsY)
			platform->animate(deltaTime);

	for (auto& object : m_unmovableObjVec)
		object->animate(deltaTime);
	for (auto& object : m_movableObjVec)
		object->animate(deltaTime);
}

//-------------------------------------------

void Level::loadLevelData(ContactListener& contactListener)
{
	m_world->SetContactListener(&contactListener);
	m_player.loadObject(m_world, m_bodyDef);
}

//-------------------------------------------

void Level::isPlayerInWindow()
{
	auto globalChordsY = getGlobalCordsY();
	//is player position bellow the view port
	if (m_player.getPosition().y + m_player.getGlobalBounds().height / 2 > globalChordsY + WIN_SIZE_Y)
		m_player.kill();
}

//-------------------------------------------

void Level::adjustView(ViewManager& gameView)
{
	auto globalChordsY = getGlobalCordsY();
	float PlayerBasePos = m_player.getBasePosition().y;
	
	//Playing the falling down illusion after collidong with an enemy
	if (!m_player.isAlive())
	{
		if(!gameView.fallDownAdjustment(m_board, globalChordsY))
			m_lvlRunnig = false;
	}
	//move the window up every time the player steps on a new platform
	else if (WIN_SIZE_Y - 350 + globalChordsY > PlayerBasePos)	//set  350 and 10 as global macro 
		gameView.basePointAdjustment(m_board, ((PlayerBasePos - WIN_SIZE_Y - globalChordsY + 350) / 10),
												globalChordsY + ((PlayerBasePos - WIN_SIZE_Y - globalChordsY + 350) / 10));

	//will be used in a case the player reached the middle of the screen without landing on any new base platform.
	//(may accure by jumping off a spring etc.) in this case, the windoe will move up with him.
	if (m_player.getPosition().y < globalChordsY + WIN_SIZE_Y/2 && m_player.isAlive())
		gameView.reachedLimitAdjustment(m_board, m_player.getPosition().y);

	gameView.setView(m_window);
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
		if(!m_player.isDying() && m_player.isAlive())
			m_board.processKeyInput(event);
	}
}

//-------------------------------------------

void Level::drawGraphics()
{
	m_window.clear(sf::Color::Black);

	if (m_board.isPaused())
		m_board.drawPauseScreen();
	else
	{
		m_board.draw();
		for (auto& platform : m_platformVec)
			platform->draw(m_window);
		for (auto& staticObj : m_unmovableObjVec)
			staticObj->draw(m_window);
		for (auto& movableObj : m_movableObjVec)
			movableObj->draw(m_window);
		for (auto& bullet : m_bullers)
			bullet->draw(m_window);
		m_player.draw(m_window);

		//we wanna draw the propellot above the player
		for (auto& movableObj : m_movableObjVec)
			if(typeid(*movableObj) == typeid(PropellerHat))
				movableObj->draw(m_window);

		if (!m_player.isAlive())
			m_player.drawStars(m_window);
		m_board.drawScoreTop();
	}
	m_window.display();
}

//--------------------------------------------

void Level::handleBulletShooting()
{
	if (m_player.hasShotBullet())
	{
		m_player.useBullet();

		addBullet();
		for (auto& bullet : m_bullers)
			bullet->shoot();
	}
}