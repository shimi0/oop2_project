#include "ScoresBoard.h"

ScoresBoard::ScoresBoard()
	:m_bgAnimation(Resources::instance().animationData(Resources::ScoresBG), Direction::Stay, m_bg)
{
	auto menuButton = std::make_unique<MenuButton>();
	m_buttons.push_back(std::move(menuButton));
	createBackGround();
}

//----------------------------------

void ScoresBoard::createBackGround()
{
	m_bg.scale(WIN_SIZE_X / m_bg.getGlobalBounds().width, WIN_SIZE_Y / m_bg.getGlobalBounds().height);
}

//------------------------------------

void ScoresBoard::draw(sf::RenderWindow& window, const std::multimap <int, std::string>& records)
{
	m_isScoresOpen = true;
	while (m_isScoresOpen)
	{
		window.clear();
		window.draw(m_bg);

		for (const auto& i : m_buttons)
			i->draw(window);
		drawScore(records, window);

		window.display();
		handleEvent(window);
	}
	m_buttons[0]->release();
}

//-------------------------------------

void ScoresBoard::handleEvent(sf::RenderWindow& window)
{

	if (auto event = sf::Event{}; window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)  window.close();

		if (event.type == sf::Event::MouseButtonReleased)
		{
			auto location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
			for (auto& button : m_buttons)
				if (button->contains(location))
					button->press();
				else
					button->release();
		}

		if (event.type == sf::Event::MouseMoved)
		{
			auto location = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
			for (auto& button : m_buttons)
				if (button->contains(location))
					button->gainFocus();
				else
					button->looseFocus();
		}
	}
	handleClick();
}

//----------------------------

void ScoresBoard::handleClick()
{
	switch (whoPreesed())
	{
	case -1:
		break;
	case 0:
		m_isScoresOpen = false;
		break;
	}
}

//---------------------

int ScoresBoard::whoPreesed()
{
	for (int i = 0; i < m_buttons.size(); i++)
		if (m_buttons[i]->isPressed())
			return i;

	return -1;
}

//-----------------------

void ScoresBoard::drawScore(const std::multimap <int, std::string>& records, sf::RenderWindow& window)
{
	std::vector<sf::Text> recordText(records.size());
	auto font = sf::Font();
	font.loadFromFile("PRISTINA.TTF");
	auto rec = records.begin();
	for (int i = 0; i < records.size(); i++, rec++)
	{
		recordText[i].setFont(font);
		recordText[i].setString(rec->second);
		recordText[i].setCharacterSize(33);
		recordText[i].setPosition(100.f, (250.f + i * 38.f));
		recordText[i].setFillColor(sf::Color::Black);
	}
	for (int i = 0; i < records.size(); i++)
		window.draw(recordText[i]);
}