#pragma once

#include "SFML/Graphics.hpp"
#include "Level.h"
#include "DataReader.h"
#include <fstream>
#include "Factory.h"
#include "GameOver.h"
#include <iostream>
#include "ScoresManager.h"

//runs the game

class Game
{
public:

	Game(sf::RenderWindow& window);
	void run(ScoresManager& scoresManager);

private:

	//reading game data using DataReader class
	void readGameData(Level& level);

	sf::RenderWindow& m_window;
	Board m_board;
};