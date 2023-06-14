#include "Game.h"
#include "Board.h"

Game::Game(sf::RenderWindow& window)
	:m_window(window)
{
}

//---------------------------

void Game::run()
{

	while (true)	//lvl.isOpen()
	{
		Level(m_window).run();


		break;
	}
}
