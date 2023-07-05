#pragma once

#include "SFML/Graphics.hpp"
#include "Level.h"
#include "DataReader.h"
#include <fstream>
#include "Factory.h"
#include "GameOver.h"
#include <iostream>
#include "ScoresManager.h"



class Game
{
public:

	Game(sf::RenderWindow& window);
	void run(ScoresManager& scoresManager);

private:

	void readGameData(Level& level);
	sf::RenderWindow& m_window;
	Board m_board;
};