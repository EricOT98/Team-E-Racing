#include "Options.h"

/// <summary>
/// Default constructor for the options screen
/// </summary>
Options::Options() : Screen(GameState::OptionsScreen)
{
	m_transitionIn = true;

	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(-1400.0f, 400.0f);

	m_titleLabel = new Label("Options", nullptr, 30.0f, sf::Vector2f(400.0f, 80.0f), endTranstionPos);
	m_titleLabel->setPosition(sf::Vector2f(900.0f, 80.0f));
	m_soundButton = new Button(focusColor, nofocusColor, fillColor, "Sound", nullptr,
		sf::Vector2f(900.0f, 150.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 150.0f), endTranstionPos);
	m_displayButton = new Button(focusColor, nofocusColor, fillColor, "Display", nullptr,
		sf::Vector2f(900.0f, 250.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 250.0f), endTranstionPos);
	m_helpButton = new Button(focusColor, nofocusColor, fillColor, "Help", nullptr,
		sf::Vector2f(900.0f, 350.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 350.0f), endTranstionPos);
	m_difficultyButton = new Button(focusColor, nofocusColor, fillColor, "Difficulty", nullptr,
		sf::Vector2f(900.0f, 450.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 450.0f), endTranstionPos);
	m_backButton = new Button(focusColor, nofocusColor, fillColor, "Back", nullptr,
		sf::Vector2f(900.0f, 550.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 550.0f), endTranstionPos);
	
	m_soundButton->promoteFocus();

	m_soundButton->m_up = m_backButton;
	m_soundButton->m_down = m_displayButton;
	m_displayButton->m_up = m_soundButton;
	m_displayButton->m_down = m_helpButton;
	m_helpButton->m_up = m_displayButton;
	m_helpButton->m_down = m_difficultyButton;
	m_difficultyButton->m_up = m_helpButton;
	m_difficultyButton->m_down = m_backButton;
	m_backButton->m_up = m_difficultyButton;
	m_backButton->m_down = m_soundButton;

	m_soundButton->select = std::bind(&Options::soundButtonCallback, this);
	m_displayButton->select = std::bind(&Options::displayButtonCallback, this);
	m_helpButton->select = std::bind(&Options::helpButtonCallback, this);
	m_difficultyButton->select = std::bind(&Options::difficultyButtonCallback, this);
	m_backButton->select = std::bind(&Options::backButtonCallback, this);

	m_gui.add(m_titleLabel);
	m_gui.add(m_soundButton);
	m_gui.add(m_displayButton);
	m_gui.add(m_helpButton);
	m_gui.add(m_difficultyButton);
	m_gui.add(m_backButton);
}

Options::~Options() { }

/// <summary>
/// If not transitioning process input for all gui objects
/// </summary>
/// <param name="controller">Current xbox 360 controller</param>
void Options::update(XboxController & controller)
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
	else if (m_backButtonSelected)
	{
		transOut(GameState::MainMenu);
	}
	else if (m_difficultyButtonSelected)
	{
		transOut(GameState::DifficultyScreen);
	}
	else if (m_displayButtonSelected)
	{
		transOut(GameState::DisplayOptionsScreen);
	}
	else if (m_helpButtonSelected)
	{
		transOut(GameState::HelpScreen);
	}
	else if (m_soundButtonSelected)
	{
		transOut(GameState::SoundOptions);
	}
	m_gui.processInput(controller);
}

/// <summary>
/// Reset the current screen
/// </summary>
void Options::reset()
{
	m_backButtonSelected = false;
	m_helpButtonSelected = false;
	m_displayButtonSelected = false;
	m_difficultyButtonSelected = false;
	m_soundButtonSelected = false;
	m_transitionIn = true;
	m_interpolation = 0.f;
}

//Callback functions
void Options::backButtonCallback()
{
	m_backButtonSelected = true;
}

void Options::helpButtonCallback()
{
	m_helpButtonSelected = true;
}

void Options::displayButtonCallback()
{
	m_displayButtonSelected = true;
}

void Options::difficultyButtonCallback()
{
	m_difficultyButtonSelected = true;
}

void Options::soundButtonCallback()
{
	m_soundButtonSelected = true;
}