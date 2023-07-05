#pragma once

#include "SFML/Graphics.hpp"
#include "Resources.h"
#include "Button.h"
#include "ScoreButton.h"
#include "ScoresBoard.h"
#include "PlayButton.h"
#include <string>
#include <map>


enum ButtonIndex
{
	PLAYBUT,
	SCORESBUT,
	MAX
};

class Menu
{
public:

	Menu(sf::RenderWindow& window, const std::multimap <int, std::string>& records);

	void run();
	void createBackGround();
	void draw();
	void handleEvent();
	void handleClick();
	ButtonIndex getPressedButton();
	void apdateAnimateDoodle();

private:

	sf::RenderWindow& m_window;

	std::vector<std::unique_ptr< Button>> m_buttons;

	ScoresBoard m_scoresBoard;

	const std::multimap <int, std::string>& m_records;

	sf::Sprite m_backGround;
	Animation m_backGroundAnimation;

	sf::Sprite m_player;
	Animation m_playerAnimation;

	sf::Sprite m_ufo;
	Animation m_ufoAnimation;


	bool m_playerGoesUp = true;
	bool m_ufoGoesUp = true;
	bool m_ufoGoesLeft = true;

	//helps drawing the animations
	int m_indexDoodle = 0;

	bool m_isMenuOpen = true;
};