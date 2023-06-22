#include "Game.h"
#include "Board.h"

Game::Game(sf::RenderWindow& window)
	:m_window(window), m_board(window)
{}

//---------------------------
//catch exceptions
void Game::run()
{
	while (true)	//lvl.isOpen()
	{
		
		auto level = Level(m_window, m_board);
		auto gameOver = GameOver(m_window, m_board);
		try
		{
			readGameData(level);
		}
		catch (std::exception& ex)
		{
			std::cerr << "Exception: " << ex.what() << '\n';
			exit(EXIT_FAILURE);
		}

		level.run();
		auto chosenButton = gameOver.run();
		if (chosenButton == PlayAgain)
			continue;
		if (chosenButton == Menu)
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
