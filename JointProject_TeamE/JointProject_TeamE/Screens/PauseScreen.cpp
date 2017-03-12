#include "PauseScreen.h"

PauseScreen::PauseScreen()
{
	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(1400.0f, 400.0f);

	m_pauseScreenLabel = new Label("Pause", nullptr, 50, sf::Vector2f(400.0f, 50.0f), endTranstionPos);
	m_resumeButton = new Button(focusColor, nofocusColor, fillColor, "Resume", nullptr, sf::Vector2f(400.0f, 150.0f),
		18, 100.0f, 40.0f, sf::Vector2f(400.0f, 150.0f), endTranstionPos);
	m_optionsButton = new Button(focusColor, nofocusColor, fillColor, "Options", nullptr, sf::Vector2f(400.0f, 250.0f),
		18, 100.0f, 40.0f, sf::Vector2f(400.0f, 250.0f), endTranstionPos);
	m_quitButton = new Button(focusColor, nofocusColor, fillColor, "Quit", nullptr, sf::Vector2f(400.0f, 350.0f),
		18, 100.0f, 40.0f, sf::Vector2f(400.0f, 350.0f), endTranstionPos);

	m_resumeButton->promoteFocus();

	m_resumeButton->m_up = m_quitButton;
	m_resumeButton->m_down = m_optionsButton;
	m_optionsButton->m_up = m_resumeButton;
	m_optionsButton->m_down = m_quitButton;
	m_quitButton->m_up = m_optionsButton;
	m_quitButton->m_down = m_resumeButton;

	m_pauseScreenGUI.add(m_pauseScreenLabel);
	m_pauseScreenGUI.add(m_resumeButton);
	m_pauseScreenGUI.add(m_optionsButton);
	m_pauseScreenGUI.add(m_quitButton);
}

PauseScreen::~PauseScreen() { }

void PauseScreen::update()
{
	m_pauseScreenGUI.update();
}

void PauseScreen::render(sf::RenderWindow &window)
{
	window.draw(m_pauseScreenGUI);
}

void PauseScreen::processInput(XboxController &controller)
{
	m_pauseScreenGUI.processInput(controller);
}