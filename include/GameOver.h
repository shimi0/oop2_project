#pragma once

#include "Resources.h"
#include "Animation.h"
#include "macros.h"
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "MenuButton.h"
#include "PlayAgainButton.h"
#include "ScoresManager.h"

//----------------------

enum choseButtons
{
	MenuButton_,
	PlayAgainButton_,
	Max
};

//----------------------

class GameOver
{

public:
	GameOver(sf::RenderWindow&, Board&, ScoresManager& scoresManager);

	choseButtons run();
	
	void setScore()
	{
		m_scoreTxt.setString(std::to_string(m_board.getScore()));
	}

private:

	choseButtons getPressedButton() const;

	bool readText(const sf::Event& event);
	void mouseMovedEvent(const sf::Event& event);
	void mouseReleasedEvent(const sf::Event& event);


	void loadData();
	void draw();
	void handleEvent();

	sf::Sprite m_spriteGameOverTXT;
	Animation m_gameOverTXT;

	sf::Sprite m_highScore;
	Animation m_highScoreAnimation;

	sf::RenderWindow& m_window;

	std::vector<std::unique_ptr< Button>> m_buttons;

	sf::Font m_font;
	sf::Text m_scoreTxt;
	sf::Text m_nameTxt;
	std::string m_playerName = {};

	bool m_nameEnterd = false;
	Board& m_board;
	ScoresManager& m_scoresManager;
};