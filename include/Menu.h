#pragma once

#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Button.h"
#include "ScoreButton.h"
#include "PlayButton.h"
#include <string>
#include <map>

//the menu screen

enum ButtonIndexMenu
{
	PLAYBUT,
	SCORESBUT,
	MAX
};

class Menu
{
public:

	Menu(sf::RenderWindow& window);

	void run();
	ButtonIndexMenu getPressedButton() const;

private:

	void createBackGround();
	void draw();
	void handleEvent();
	void handleClick();
	void apdateAnimateDoodle();

	sf::RenderWindow& m_window;

	std::vector<std::unique_ptr< Button>> m_buttons;

	//menu background
	sf::Sprite m_backGround;
	Animation m_backGroundAnimation;

	//the menu player animation
	sf::Sprite m_player;
	Animation m_playerAnimation;
	//helps drawing the animations
	bool m_playerGoesUp = true;
	int m_indexDoodle = 0;

	//the menu's ufo animation
	sf::Sprite m_ufo;
	Animation m_ufoAnimation;

	bool m_isMenuOpen = true;
};