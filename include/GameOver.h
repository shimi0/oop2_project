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
	MenuB_,
	PlayAgainB_,
};

class GameOver
{

public:
	GameOver(sf::RenderWindow&, Board&);

	chosenButton run();
	void setScore()
	{
		m_scoreTxt.setString(std::to_string(m_board.getScore()));
	}

private:

	void loadData();

	sf::Sprite m_spriteGameOverTXT;
	Animation m_gameOverTXT;

	sf::Sprite m_highScore;
	Animation m_highScoreAnimation;

	sf::RenderWindow& m_window;
	MenuButton m_menuButton;
	PlayAgainButton m_playAgainButton;

	sf::Font m_font;
	sf::Text m_scoreTxt;
	
	Board& m_board;
};