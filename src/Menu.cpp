#include "Menu.h"

Menu::Menu(sf::RenderWindow& window)
	:m_window(window),
	m_backGroundAnimation(Resources::instance().animationData(Resources::MenuBG), Direction::Stay, m_backGround),
	m_playerAnimation(Resources::instance().animationData(Resources::DoodleClassic), Direction::Right, m_player),
	m_ufoAnimation(Resources::instance().animationData(Resources::Ufo), Direction::Stay, m_ufo),m_buttons(MAX)
{
	createBackGround();
}

//----------------------

void Menu::run()
{
	m_window.setTitle("Doodle Jump - Menu");
	sf::Clock clock;
	
	while (m_isMenuOpen)
	{
		auto deltaTime = clock.restart();
		draw();

		m_ufoAnimation.updateBasedOnTime(deltaTime + deltaTime);
		handleEvent();
	}
}

//---------------------------------------
void Menu::createBackGround()
{
	auto playButton = std::make_unique<PlayButton>();
	m_buttons[PLAYBUT] = (std::move(playButton));
	//auto optionsButton = std::make_unique<OptionsButton>();
	//m_buttons.push_back(std::move(optionsButton));
	auto scoresButton = std::make_unique<ScoreButton>();
	m_buttons[SCORESBUT] = (std::move(scoresButton));

	m_backGround.scale(WIN_SIZE_X / m_backGround.getGlobalBounds().width, WIN_SIZE_Y / m_backGround.getGlobalBounds().height);
	m_player.setPosition(WIN_SIZE_X / 7, WIN_SIZE_Y * 2 / 3);
	m_player.setScale({ 2,2 });
	m_ufo.setScale({ 2,2 });
	m_ufo.setPosition(WIN_SIZE_X * 2 / 3 , WIN_SIZE_Y / 8);
}

//----------------------
void Menu::draw()
{
	m_window.clear();
	m_window.draw(m_backGround);
	m_window.draw(m_player);
	m_window.draw(m_ufo);

	for (const auto& button : m_buttons)
		button->draw(m_window);
	m_window.display();
	apdateAnimateDoodle();
}

//------------------
void Menu::handleEvent()
{
	if (auto event = sf::Event{}; m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)  m_window.close();
			
		if (event.type == sf::Event::MouseButtonReleased)
		{
			auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
			for (auto& button : m_buttons)
				if (button->contains(location))
					button->press();
				else
					button->release();
		}

		if (event.type == sf::Event::MouseMoved)
		{
			auto location = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
			for (auto& button : m_buttons)
				if (button->contains(location))
					button->gainFocus();
				else
					button->looseFocus();
		}
	}
	handleClick();
}
//-----------------
void Menu::handleClick()
{
	switch (getPressedButton())
	{
		case MAX:								 break;
		case PLAYBUT:
		case SCORESBUT:  m_isMenuOpen = false;   break;
	}
}
//---------------------
ButtonIndexMenu Menu::getPressedButton() const
{
	for (int i = 0; i < m_buttons.size(); i++)
		if (m_buttons[i]->isPressed())
			return ButtonIndexMenu(i);

	return ButtonIndexMenu::MAX;
}

//-------------------------
void Menu::apdateAnimateDoodle()
{
	m_indexDoodle++;
	if (m_playerGoesUp)
		m_player.setPosition(m_player.getPosition().x, m_player.getPosition().y - 4);
	else
		m_player.setPosition(m_player.getPosition().x, m_player.getPosition().y + 4);

	if (m_indexDoodle > 120)
	{
		m_playerGoesUp = !m_playerGoesUp;
		m_indexDoodle = 0;
	}
}