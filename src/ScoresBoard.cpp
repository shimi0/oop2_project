#include "ScoresBoard.h"

ScoresBoard::ScoresBoard(sf::RenderWindow& window, const std::multimap <int, std::string, std::greater<int>>& records)
	:m_bgAnimation(Resources::instance().animationData(Resources::ScoresBG), Direction::Stay, m_bg),
	m_buttons(MAX_S), m_window(window), m_recordList(records)
{
	auto menuButton = std::make_unique<MenuButton>();
	m_buttons[MENU_BUTTON] = (std::move(menuButton));
	createBackGround();
}

//----------------------------------------------

void ScoresBoard::run()
{
	m_window.setTitle("Doodle Jump - Scores");
	while (m_isScoresOpen)
	{
		draw();
		handleEvent(m_window);
	}
}

//----------------------------------------------

void ScoresBoard::createBackGround()
{
	m_bg.scale(WIN_SIZE_X / m_bg.getGlobalBounds().width, WIN_SIZE_Y / m_bg.getGlobalBounds().height);
}

//----------------------------------------------

void ScoresBoard::draw()
{
	m_window.clear();
	m_window.draw(m_bg);

	for (const auto& i : m_buttons)
		i->draw(m_window);
	drawScore();

	m_window.display();
}

//-------------------------------------

void ScoresBoard::handleEvent(sf::RenderWindow& window)
{

	if (auto event = sf::Event{}; window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)  window.close();

		if (event.type == sf::Event::MouseButtonReleased)
			mouseReleasedEvent(event);

		if (event.type == sf::Event::MouseMoved)
			mouseMovedEvent(event);
	}
	handleClick();
}

//----------------------------

void ScoresBoard::handleClick()
{
	switch (getPressedButton())
	{
		case MENU_BUTTON: m_isScoresOpen = false; break;
		default:
			break;
	}
}

//---------------------

ButtonIndexScore ScoresBoard::getPressedButton()
{
	for (int i = 0; i < m_buttons.size(); i++)
		if (m_buttons[i]->isPressed())
			return ButtonIndexScore(i);

	return ButtonIndexScore::MAX_S;
}

//-----------------------

void ScoresBoard::drawScore()
{
	std::vector<sf::Text> recordText(m_recordList.size());
	auto font = sf::Font();
	font.loadFromFile("PRISTINA.TTF");
	auto rec = m_recordList.begin();

	for (int i = 0; i < m_recordList.size(); i++, rec++)
	{
		recordText[i].setFont(font);
		recordText[i].setString(rec->second);
		recordText[i].setCharacterSize(70);
		recordText[i].setPosition(WIN_SIZE_X / 5.1, WIN_SIZE_Y / 4.6 + i * WIN_SIZE_Y/ 21.5);
		recordText[i].setFillColor(sf::Color::Black);
	}

	for (int i = 0; i < m_recordList.size(); i++)
		m_window.draw(recordText[i]);
}

//--------------------------------------

void ScoresBoard::mouseMovedEvent(const sf::Event& event)
{
	auto location = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
	for (auto& button : m_buttons) {
		if (button->contains(location))
			button->gainFocus();
		else
			button->looseFocus();
	}
}

//----------------------------------------------

void ScoresBoard::mouseReleasedEvent(const sf::Event& event)
{
	auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
	for (auto& button : m_buttons) {
		if (button->contains(location))
			button->press();
		else
			button->release();
	}
}

//----------------------------------------------