#include "GameOverScreen.h"

/// <summary>
/// Initialise the gui objects for teh gae over screen
/// </summary>
GameOverScreen::GameOverScreen() : Screen(GameState::EndGameState)
{
	m_transitionIn = true;

	sf::Color focusColor = sf::Color::Red;
	sf::Color noFocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;
	sf::Vector2f endTransitionPos = sf::Vector2f(-1400, 400.0f);

	m_titleLabel = new Label("Game Over", nullptr, 30.0f, sf::Vector2f(400.0f, 80.0f), endTransitionPos);
	m_titleLabel->setPosition(sf::Vector2f(900.0f, 80.0f));

	m_fastestLapTimeLabel = new Label("Fastest Lap time", nullptr, 30.0f, sf::Vector2f(400.0f, 120.0f), endTransitionPos);
	m_fastestLapTimeLabel->setPosition(sf::Vector2f(900.0f, 120.0f));

	m_backButton = new Button(focusColor, noFocusColor, fillColor, "Back to Menu", nullptr,
		sf::Vector2f(-100.0f, 450.0f), 18, 200.0f, 40.0f, sf::Vector2f(300.0f, 450.0f), endTransitionPos);
	m_quitButton = new Button(focusColor, noFocusColor, fillColor, "Quit to Exit", nullptr,
		sf::Vector2f(900.0f, 450.0f), 18, 200.0f, 40.0f, sf::Vector2f(500.0f, 450.0f), endTransitionPos);

	m_backButton->promoteFocus();

	m_backButton->m_left = m_quitButton;
	m_backButton->m_right = m_quitButton;
	m_quitButton->m_left = m_backButton;
	m_quitButton->m_right = m_backButton;
	m_backButton->select = std::bind(&GameOverScreen::backToMenuCallback, this);
	m_quitButton->select = std::bind(&GameOverScreen::quitGameCallback, this);

	m_gui.add(m_titleLabel);
	m_gui.add(m_backButton);
	m_gui.add(m_fastestLapTimeLabel);
	m_gui.add(m_quitButton);
}

/// <summary>
/// Default destructor for GameOverScreen
/// </summary>
GameOverScreen::~GameOverScreen()
{
}

/// <summary>
/// If transitioning update the gui components position
/// else process input
/// </summary>
/// <param name="controller"></param>
void GameOverScreen::update(XboxController & controller)
{
	if (m_transitionIn) {
		m_gui.transitionIn(0.03f, m_interpolation);

		if (m_interpolation >= 1.0f) {
			m_transitionIn = false;
			m_interpolation = 0.0f;
		}
	}
	else if (m_backButtonSelected) {
		transOut(GameState::MainMenu);
	}
	else if (m_quitButtonSelected) {
		transOut(GameState::MainMenu);
		std::cout << "Quit" << std::endl;
	}
	m_gui.processInput(controller);
}

/// <summary>
/// Reset the current screen
/// </summary>
void GameOverScreen::reset()
{
	m_backButtonSelected = false;
	m_quitButtonSelected = false;
	m_transitionIn = true;
	m_interpolation = 0.f;
}

/// <summary>
/// Back to menu callback
/// </summary>
void GameOverScreen::backToMenuCallback()
{
	m_backButtonSelected = true;
}

/// <summary>
/// Quit Game Call back
/// </summary>
void GameOverScreen::quitGameCallback()
{
	m_quitButtonSelected = true;
}
