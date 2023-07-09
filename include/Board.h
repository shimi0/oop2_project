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
	
	//board position based on the window-view
	void updateBGPos(const sf::Vector2f& newPos);
	void resetBoardPosition() { updateBGPos({ 0,0 }); }

	void processKeyInput(const sf::Event& event);
	bool isPaused() const { return m_pauseButton.isPressed(); }

	void draw();
	void drawScoreTop();
	void drawPauseScreen();

	void updateScore(const int score);
	int getScore() const {	return m_score; }

private:

	void drawBG();
	void loadScoreTxt();

	sf::RenderWindow& m_window;

	//background
	sf::Sprite m_spriteBG;
	Animation m_animationBG;
	
	//score background
	sf::Sprite m_scoreTop;
	Animation m_scoreTopAnimation;

	//bause screen background
	sf::Sprite m_PauseScreen;
	Animation m_pauseScreenAnimation;

	//score
	sf::Text m_scoreTxt;
	sf::Font m_font;
	int m_score = 0;

	PauseButton m_pauseButton;
};