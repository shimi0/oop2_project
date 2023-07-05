#pragma once

#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Animation.h"
#include "box2d/box2d.h"
#include "macros.h"
#include "PauseButton.h"
#include "Font.h"

//prints the in-game board, background and the in-game score

class Board
{
public:

	Board(sf::RenderWindow& window);
	void draw();
	void updateBGPos(const sf::Vector2f newPos);

	void processKeyInput(const sf::Event& event);

	void resetBoardPosition() { updateBGPos({ 0,0 }); }

	void drawScoreTop();


	bool isPaused() const { return m_pauseButton.isPressed(); }
	
	void drawPauseScreen();

	void updateScore(const int score);

	int getScore() const {	return m_score; }

private:

	void drawBG();
	void loadScoreTxt();
	int m_score = 0;

	sf::RenderWindow& m_window;
	sf::Sprite m_spriteBG;
	Animation m_animationBG;
	
	sf::Sprite m_scoreTop;
	Animation m_scoreTopAnimation;

	sf::Sprite m_PauseScreen;
	Animation m_pauseScreenAnimation;

	sf::Text m_scoreTxt;
	sf::Font m_font;
	PauseButton m_pauseButton;
};