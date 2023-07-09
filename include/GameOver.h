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

//game over screen

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
	
	void setScore();

private:

	choseButtons getPressedButton() const;
	
	//read the user name
	void handleEvent();
	bool readText(const sf::Event& event);
	void mouseMovedEvent(const sf::Event& event);
	void mouseReleasedEvent(const sf::Event& event);

	void loadScoreTxt();
	void loadNameTxt();

	void loadData();
	void draw();

	//game over text
	sf::Sprite m_spriteGameOverTXT;
	Animation m_gameOverTXT;

	//high score text
	sf::Sprite m_highScore;
	Animation m_highScoreAnimation;

	sf::RenderWindow& m_window;

	//game over buttons
	std::vector<std::unique_ptr< Button>> m_buttons;

	sf::Font m_font;
	sf::Text m_scoreTxt;
	sf::Text m_nameTxt;
	std::string m_playerName = {};

	bool m_nameEnterd = false;
	Board& m_board;
	ScoresManager& m_scoresManager;
};