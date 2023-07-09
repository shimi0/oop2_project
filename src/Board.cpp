#include "Board.h"

Board::Board(sf::RenderWindow& window)
	:m_window(window), m_animationBG(Resources::instance().animationData(Resources::BackGroundClassic), Direction::Stay, m_spriteBG),
	 m_scoreTopAnimation(Resources::instance().animationData(Resources::ScoreTopClassic), Direction::Stay, m_scoreTop),
	 m_pauseScreenAnimation(Resources::instance().animationData(Resources::PauseScreen), Direction::Stay, m_PauseScreen),
	 m_pauseButton()
{
	loadScoreTxt();
}

//------------------------------------------------

void Board::draw()
{
	drawBG();
}

//------------------------------------------------

void Board::updateBGPos(const sf::Vector2f& newPos)
{
	m_spriteBG.setPosition(newPos);
	m_scoreTop.setPosition(newPos);
	m_scoreTxt.setPosition(newPos);
	m_PauseScreen.setPosition(newPos);
	m_pauseButton.setPosition(sf::Vector2f( WIN_SIZE_X * 20 / 22, m_scoreTop.getPosition().y + m_scoreTop.getGlobalBounds().height / 2.8));
	
}

//------------------------------------------------

void Board::processKeyInput(const sf::Event& event)
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

//------------------------------------------------

void Board::drawPauseScreen()
{
	m_PauseScreen.scale(640 * 2 / m_PauseScreen.getGlobalBounds().width, 1024 * 2 / m_PauseScreen.getGlobalBounds().height);
	m_window.draw(m_PauseScreen);
}

//------------------------------------------------

void Board::updateScore(const int score)
{
	m_score = score;
	m_scoreTxt.setString(std::to_string(score));
}

//------------------------------------------------
																															//==|
void Board::drawBG()																										//==|
{																															//==|
		//----------TO_DO: biger scale for the bg. only in my pc- bigger resolutin. change!!!!----------------------------------|

	m_spriteBG.scale(640 * 2 / m_spriteBG.getGlobalBounds().width, 1024 * 2 / m_spriteBG.getGlobalBounds().height);
	m_window.draw(m_spriteBG);
	m_spriteBG.setScale(1, 1);
}

//------------------------------------------------

void Board::loadScoreTxt()
{
	if (!m_font.loadFromFile("PRISTINA.TTF"))
		throw std::runtime_error("unable to load font");

	m_scoreTxt.setFont(m_font);
	m_scoreTxt.setFillColor(sf::Color::Black);
	m_scoreTxt.setOrigin(m_scoreTxt.getGlobalBounds().width / 2, m_scoreTxt.getGlobalBounds().height / 2);
	//m_scoreTxt.setPosition()
	m_scoreTxt.scale({ 1.5,1.5 });
	m_scoreTxt.setString("0");
}

//------------------------------------------------

void Board::drawScoreTop()
{
	m_scoreTop.scale(640 * 2 / m_scoreTop.getGlobalBounds().width, (WIN_SIZE_Y / 18) / m_scoreTop.getGlobalBounds().height);
	m_window.draw(m_scoreTop);
	m_pauseButton.draw(m_window);
	m_window.draw(m_scoreTxt);
}



