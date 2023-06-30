#include "GameOver.h"

GameOver::GameOver(sf::RenderWindow& window, Board& board)
	:m_gameOverTXT(Resources::instance().animationData(Resources::GameOver), Direction::Stay, m_spriteGameOverTXT),
	 m_highScoreAnimation(Resources::instance().animationData(Resources::HighScore), Direction::Stay, m_highScore),
	m_window(window), m_board(board), m_menuButton(), m_playAgainButton()
{}


//--------------------------------------------

chosenButton GameOver::run()
{

	loadData();
	setScore();
	while (m_window.isOpen())
	{
		m_window.clear(sf::Color::Black);
		m_board.draw();
		m_window.draw(m_spriteGameOverTXT);
		m_window.draw(m_highScore);
		m_window.draw(m_scoreTxt);
		m_menuButton.draw(m_window);
		m_playAgainButton.draw(m_window);
		m_window.display();

		sf::Event event;
		while (m_window.pollEvent(event))
		{
		
			if (event.type == sf::Event::Closed)
			{
				
				m_window.close();
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

				if (m_menuButton.contains(location))
				{
					m_menuButton.press();
					m_playAgainButton.release();
					return MenuB_;
				}
				else if (m_playAgainButton.contains(location))
				{
					m_playAgainButton.press();
					m_menuButton.release();
					return PlayAgainB_;
				}
				else
				{
					m_playAgainButton.release();
					m_menuButton.release();
				}

			}
			
			if (event.type == sf::Event::MouseMoved)
			{
				auto location = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });

				if (m_menuButton.contains(location))
				{
					m_menuButton.gainFocus();
					m_playAgainButton.looseFocus();
				}
				else if (m_playAgainButton.contains(location))
				{
					m_playAgainButton.gainFocus();
					m_menuButton.looseFocus();
				}
				else
				{
					m_menuButton.looseFocus();
					m_playAgainButton.looseFocus();
				}
			}
		}

	}
}

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


	if (!m_font.loadFromFile("c:/Windows/Fonts/Arial.ttf"))
		throw std::runtime_error("unable to load font");

	m_scoreTxt.setFont(m_font);
	m_scoreTxt.setFillColor(sf::Color::Black);
	m_scoreTxt.setOrigin(m_scoreTxt.getGlobalBounds().width / 2, m_scoreTxt.getGlobalBounds().height / 2);
	m_scoreTxt.setPosition(m_highScore.getPosition().x + m_highScore.getGlobalBounds().width /2 + 10, m_highScore.getPosition().y - m_highScore.getGlobalBounds().height/2 + 10);
	m_scoreTxt.scale({ 1.5,1.5 });
	m_scoreTxt.setString("0");
}

//--------------------------------------------

//sf::Texture texture;
//texture.create(m_window.getSize().x, m_window.getSize().y);
//
//// Copy the contents of the window to the texture
//texture.update(m_window);
//
//// Save the texture as an image
//texture.copyToImage().saveToFile("screenshot.png");