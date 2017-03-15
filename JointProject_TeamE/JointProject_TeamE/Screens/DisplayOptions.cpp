#include "DisplayOptions.h"

DisplayOptions::DisplayOptions() : Screen(GameState::DisplayOptionsScreen)
{
	m_transitionIn = true;

	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(900.0f, 900.0f);

	m_titleLabel = new Label("Display Opitions", nullptr, 50,
		sf::Vector2f(400.0f, 50.0f), endTranstionPos);
	m_titleLabel->setPosition(endTranstionPos);
	m_backButton = new Button(focusColor, nofocusColor, fillColor, "Back", nullptr, 
		sf::Vector2f(-500.0f, -400.0f), 18, 100.0f, 40.0f, sf::Vector2f(400.0f, 500.0f), endTranstionPos);

	m_backButton->promoteFocus();

	m_backButton->select = std::bind(&DisplayOptions::backButtonCallback, this);

	m_gui.add(m_titleLabel);
	m_gui.add(m_backButton);
}

DisplayOptions::~DisplayOptions() { }

void DisplayOptions::update(XboxController & controller)
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
		transOut(GameState::OptionsScreen);
	}
	m_gui.processInput(controller);
}

void DisplayOptions::reset()
{
	m_transitionIn = true;
	m_interpolation = 0.f;
	m_backButtonSelected = false;
}

void DisplayOptions::backButtonCallback()
{
	m_backButtonSelected = true;
}