#include "MainMenu.h"

MainMenu::MainMenu(bool & gameReset) : Screen(GameState::MainMenu), m_gameReset(gameReset)
{
	m_transitionIn = true;

	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(1400.0f, 400.0f);

	// Assign the pointers on the heap
	m_playButton = new Button(focusColor, nofocusColor, fillColor, "Race!", nullptr,
		sf::Vector2f(400.0f, 50.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 50.0f), endTranstionPos);
	m_upgradesButton = new Button(focusColor, nofocusColor, fillColor, "Upgrades", nullptr,
		sf::Vector2f(400.0f, 150.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 150.0f), endTranstionPos);
	m_trophiesButton = new Button(focusColor, nofocusColor, fillColor, "Trophies", nullptr,
		sf::Vector2f(400.0f, 250.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 250.0f), endTranstionPos);
	m_optionsButton = new Button(focusColor, nofocusColor, fillColor, "Options", nullptr,
		sf::Vector2f(400.0f, 350.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 350.0f), endTranstionPos);
	m_creditsButton = new Button(focusColor, nofocusColor, fillColor, "Credits", nullptr,
		sf::Vector2f(400.0f, 450.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 450.0f), endTranstionPos);
	m_exitButton = new Button(focusColor, nofocusColor, fillColor, "Exit", nullptr,
		sf::Vector2f(400.0f, 550.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 550.0f), endTranstionPos);

	// Promote the focus of one widget
	m_playButton->promoteFocus();
	 // Set the directional commands of all of the widgets
	m_playButton->m_up = m_exitButton;
	m_playButton->m_down = m_upgradesButton;
	m_upgradesButton->m_up = m_playButton;
	m_upgradesButton->m_down = m_trophiesButton;
	m_trophiesButton->m_up = m_upgradesButton;
	m_trophiesButton->m_down = m_optionsButton;
	m_optionsButton->m_up = m_trophiesButton;
	m_optionsButton->m_down = m_creditsButton;
	m_creditsButton->m_up = m_optionsButton;
	m_creditsButton->m_down = m_exitButton;
	m_exitButton->m_up = m_creditsButton;
	m_exitButton->m_down = m_playButton;

	// Assign Callbacks
	m_playButton->select = std::bind(&MainMenu::playButtonCallback, this);
	m_upgradesButton->select = std::bind(&MainMenu::upgradesButtonCallback, this);
	m_trophiesButton->select = std::bind(&MainMenu::trophiesButtonCallback, this);
	m_optionsButton->select = std::bind(&MainMenu::optionsButtonCallback, this);
	m_creditsButton->select = std::bind(&MainMenu::creditsButtonCallback, this);
	m_exitButton->select = std::bind(&MainMenu::exitButtonCallback, this);

	// Add the widgets to the gui
	m_gui.add(m_playButton);
	m_gui.add(m_upgradesButton);
	m_gui.add(m_trophiesButton);
	m_gui.add(m_optionsButton);
	m_gui.add(m_creditsButton);
	m_gui.add(m_exitButton);

	m_gui.update();
}

MainMenu::~MainMenu() { }

void MainMenu::update(XboxController & controller)
{
	if (m_transitionIn)
	{
		m_gui.transitionIn(0.05f, m_interpolation);
		if (m_interpolation >= 1.0f)
		{
			m_interpolation = 0.0f; // Reset the interpolation
			m_transitionIn = false;
		}
	}
	else if (m_playButtonSelected)
	{
		transOut(GameState::SelectCarScreen);
	}
	else if (m_upgradesButtonSelected)
	{
		transOut(GameState::UpgradesScreen);
	}
	else if (m_trophiesButtonSelected)
	{
		transOut(GameState::TrophyScreen);
	}
	else if (m_optionsButtonSelected)
	{
		transOut(GameState::OptionsScreen);
	}
	else if (m_creditsButtonSelected)
	{
		transOut(GameState::CreditsScreen);
	}
	else if (m_exitButtonSelected)
	{
		transOut(GameState::QuitScreen);
	}
	m_gui.processInput(controller);
}

void MainMenu::render(sf::RenderWindow &window)
{
	window.draw(m_gui); // Draw the GUI object
}

void MainMenu::reset()
{
	m_creditsButtonSelected = false;
	m_playButtonSelected = false;
	m_optionsButtonSelected = false;
	m_exitButtonSelected = false;
	m_upgradesButtonSelected = false;
	m_trophiesButtonSelected = false;
	m_transitionIn = true;
	m_gameReset = true;
}



void MainMenu::playButtonCallback()
{
	m_playButtonSelected = true;
}

void MainMenu::creditsButtonCallback()
{
	m_creditsButtonSelected = true;
}

void MainMenu::exitButtonCallback()
{
	m_exitButtonSelected = true;
}

void MainMenu::optionsButtonCallback()
{
	m_optionsButtonSelected = true;
}

void MainMenu::upgradesButtonCallback()
{
	m_upgradesButtonSelected = true;
}

void MainMenu::trophiesButtonCallback()
{
	m_trophiesButtonSelected = true;
}