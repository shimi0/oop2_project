#pragma once

#include "Resources.h"
#include "Animation.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "MenuButton.h"
#include "PlayAgainButton.h"

enum chosenButton
{
	Menu,
	PlayAgain,
};

class GameOver
{

public:
	GameOver(sf::RenderWindow&, Board&);

	chosenButton run();


private:

	void loadData();

	sf::Sprite m_spriteGameOverTXT;
	Animation m_gameOverTXT;

	sf::RenderWindow& m_window;
	MenuButton m_menuButton;
	PlayAgainButton m_playAgainButton;
	
	Board& m_board;
};