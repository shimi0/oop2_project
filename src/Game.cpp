#include "Game.h"
#include "Board.h"

Game::Game(sf::RenderWindow& window)
	:m_window(window), m_board(window)
{}

//---------------------------

void Game::run(ScoresManager& scoresManager)
{
	m_window.setTitle("Doodle Jump");

	while (true)
	{
		auto level = Level(m_window, m_board);
		auto gameOver = GameOver(m_window, m_board, scoresManager);

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
		if (chosenButton == PlayAgainButton_)
			continue;
		if (chosenButton == MenuButton_)
			break;
	}
}

//---------------------------

void Game::readGameData(Level& level)
{
	auto dataReader = DataReader("LVL" + std::to_string(LEVEL_FILE_NUM) + ".txt");
	dataReader.openFile();
	Object object;

	while (!dataReader.isEOF())
	{
		object = dataReader.readObject();
		level.addObject(object.type, object.position);
	}
}
