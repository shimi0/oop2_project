#include "GameOver.h"

GameOver::GameOver(sf::RenderWindow& window, Board& board, ScoresManager& scoresManager)
	:m_gameOverTXT(Resources::instance().animationData(Resources::GameOver), Direction::Stay, m_spriteGameOverTXT),
	 m_highScoreAnimation(Resources::instance().animationData(Resources::HighScore), Direction::Stay, m_highScore),
	m_window(window), m_board(board), m_buttons(Max), m_scoresManager(scoresManager)
{
	auto playButton = std::make_unique<PlayAgainButton>();
	m_buttons[PlayAgainButton_] = (std::move(playButton));
	auto scoresButton = std::make_unique<MenuButton>();
	m_buttons[MenuButton_] = (std::move(scoresButton));
}

//--------------------------------------------

choseButtons GameOver::run()
{
	loadData();
	setScore();

	while (m_window.isOpen())
	{
		draw();
		handleEvent();
		if (getPressedButton() != Max && m_nameEnterd)
		{
			if (m_scoresManager.isRecord(m_board.getScore()))
				m_scoresManager.addRecord(m_window, m_board.getScore(), m_playerName);
			return getPressedButton();
		}
	}
}

//----------------------------------------

void GameOver::draw()
{
	m_window.clear(sf::Color::Black);
	m_board.draw();
	m_window.draw(m_spriteGameOverTXT);
	m_window.draw(m_highScore);
	m_window.draw(m_scoreTxt);
	m_window.draw(m_nameTxt);
	m_nameTxt.setString(m_playerName);
	for (auto& button : m_buttons)
		button->draw(m_window);
	m_window.display();
}

//----------------------------------------

void GameOver::handleEvent()
{
	if (auto event = sf::Event{}; m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)  m_window.close();

		if (event.type == sf::Event::MouseButtonReleased)
			mouseReleasedEvent(event);

		if (event.type == sf::Event::MouseMoved)
			mouseMovedEvent(event);

		if (event.type == sf::Event::TextEntered && !m_nameEnterd) 
			m_nameEnterd = readText(event);
	}
}

//----------------------------------------------

bool GameOver::readText(const sf::Event& event)
{
	if (event.text.unicode < 128 && event.text.unicode>94)
		m_playerName += static_cast<char>(event.text.unicode);

	if (event.text.unicode == 13 || m_playerName.length() == 15)
		return true;
	return false;
}

//----------------------------------------------

void GameOver::mouseMovedEvent(const sf::Event& event)
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

void GameOver::mouseReleasedEvent(const sf::Event& event)
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

void GameOver::loadData()
{
	auto view = m_window.getView();
	view.reset(sf::FloatRect(0, 0, WIN_SIZE_X, WIN_SIZE_Y));
	m_window.setView(view);
	m_board.resetBoardPosition();
	
	m_spriteGameOverTXT.setOrigin(m_spriteGameOverTXT.getGlobalBounds().width / 2, m_spriteGameOverTXT.getGlobalBounds().height / 2);
	m_spriteGameOverTXT.scale(2, 2);
	m_spriteGameOverTXT.setPosition(WIN_SIZE_X / 2, WIN_SIZE_Y / 3);

	m_highScore.setOrigin(m_highScore.getGlobalBounds().width / 2, m_highScore.getGlobalBounds().height / 2);
	m_highScore.scale(2, 2);
	m_highScore.setPosition(WIN_SIZE_X / 2, WIN_SIZE_Y /2);

	if (!m_font.loadFromFile("PRISTINA.TTF"))
		throw std::runtime_error("unable to load font");

	m_scoreTxt.setFont(m_font);
	m_scoreTxt.setFillColor(sf::Color::Black);
	m_scoreTxt.setOrigin(m_scoreTxt.getGlobalBounds().width / 2, m_scoreTxt.getGlobalBounds().height / 2);
	m_scoreTxt.setPosition(m_highScore.getPosition().x + m_highScore.getGlobalBounds().width /2 + 20, m_highScore.getPosition().y - m_highScore.getGlobalBounds().height/2 - 10);
	m_scoreTxt.scale({ 1.7,1.7 });
	m_scoreTxt.setCharacterSize(40);
	m_scoreTxt.setFillColor(sf::Color::Red);
	m_scoreTxt.setString("0");

	m_nameTxt.setFont(m_font);
	m_nameTxt.setFillColor(sf::Color::Red);
	m_nameTxt.setPosition(m_highScore.getPosition().x + m_highScore.getGlobalBounds().width / 2 - 100, m_highScore.getPosition().y + m_highScore.getGlobalBounds().height / 2 - 120);
	m_nameTxt.setCharacterSize(70);

}

//---------------------------------------------------------

choseButtons GameOver::getPressedButton() const
{
	for (int i = 0; i < m_buttons.size(); i++)
		if (m_buttons[i]->isPressed())
			return choseButtons(i);

	return choseButtons::Max;
}