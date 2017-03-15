#include "PauseScreen.h"

PauseScreen::PauseScreen() : Screen(GameState::PauseScreen)
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

	m_resumeButton->select = std::bind(&PauseScreen::resumeButtonCallback, this);
	m_optionsButton->select = std::bind(&PauseScreen::optionsButtonCallback, this);
	m_quitButton->select = std::bind(&PauseScreen::quitButtonCallback, this);

	m_gui.add(m_pauseScreenLabel);
	m_gui.add(m_resumeButton);
	m_gui.add(m_optionsButton);
	m_gui.add(m_quitButton);
}

PauseScreen::~PauseScreen() { }

void PauseScreen::update(XboxController & controller)
{
	if (m_transitionIn)
	{
		m_gui.transitionIn(0.03f, m_interpolation);

		if (m_interpolation >= 1.0f)
		{
			m_transitionIn = false;
			m_interpolation = 0.0f;
		}
	}
	else if (m_resumeSelected)
	{
		// Code Here...
	}
	else if (m_optionsSelected)
	{
		//Code Here...
	}
	else if (m_quitSelected)
	{
		//Code here...
	}
	m_gui.processInput(controller);
}

void PauseScreen::reset()
{
	m_interpolation = 0.f;
	m_transitionIn = true;
	m_resumeSelected = false;
	m_optionsSelected = false;
	m_quitSelected = false;
}

void PauseScreen::resumeButtonCallback()
{
	m_resumeSelected = true;
}

void PauseScreen::optionsButtonCallback()
{
	m_optionsSelected = true;
}

void PauseScreen::quitButtonCallback()
{
	m_quitSelected = true;
}