#include "Game.h"
#include "Board.h"

Game::Game(sf::RenderWindow& window)
	:m_window(window)
{}

//---------------------------
//catch exceptions
void Game::run()
{
	while (true)	//lvl.isOpen()
	{
		auto level = Level(m_window);
		readGameData(level);

		level.run();

		break;
	}
}

//---------------------------

void Game::readGameData(Level& level)
{
	auto dataReader = DataReader("LVL1.txt");
	dataReader.openFile();
	Object object;

	while (!dataReader.isEOF())
	{
		object = dataReader.readObject();
		level.addObject(object.type, object.position);
	}
}
