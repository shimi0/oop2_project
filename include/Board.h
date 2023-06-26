#pragma once

#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Animation.h"
#include "box2d/box2d.h"
#include "macros.h"
#include "PauseButton.h"
#include "Font.h"

class Board
{
public:

	Board(sf::RenderWindow& window);
	void draw();
	void updateBGPos(const sf::Vector2f newPos);

	void processKeyInput(const sf::Event& event)
	{
		if (event.type == sf::Event::MouseButtonReleased)
		{
			auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
			if (m_pauseButton.contains(location))
			{
				if (m_pauseButton.isPressed())
					m_pauseButton.release();
				else
				{
					m_pauseButton.press();
				}
			}

		}
	}

	void resetBoardPosition()
	{
		updateBGPos({ 0,0 });
	}

	void drawScoreTop();


	bool isPaused() const
	{
		return m_pauseButton.isPressed();
	}
	
	void drawPauseScreen()
	{
		m_PauseScreen.scale(640 * 2 / m_PauseScreen.getGlobalBounds().width, 1024 * 2 / m_PauseScreen.getGlobalBounds().height);
		m_window.draw(m_PauseScreen);
	}

private:

	void drawBG();
	

	sf::RenderWindow& m_window;
	sf::Sprite m_spriteBG;
	Animation m_animationBG;
	
	sf::Sprite m_scoreTop;
	Animation m_scoreTopAnimation;

	sf::Sprite m_PauseScreen;
	Animation m_pauseScreenAnimation;

	Font m_font;
	PauseButton m_pauseButton;
};