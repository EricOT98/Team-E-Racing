#include "DisplayOptions.h"

DisplayOptions::DisplayOptions(bool & shaderIn) : Screen(GameState::DisplayOptionsScreen),
												  m_shader(shaderIn)
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
	m_checkbox = new CheckBox(focusColor, nofocusColor, fillColor, "Toggle Shader", nullptr, sf::Vector2f(400.0f, -400.0f),
		22, 80.0f, 80.0f, sf::Vector2f(400.0f, 300.0f), endTranstionPos);
	m_checkbox->promoteFocus();

	m_backButton->select = std::bind(&DisplayOptions::backButtonCallback, this);
	m_checkbox->select = std::bind(&DisplayOptions::checkboxCallback, this);

	m_backButton->m_up = m_checkbox;
	m_backButton->m_down = m_checkbox;
	m_checkbox->m_up = m_backButton;
	m_checkbox->m_down = m_backButton;
	m_checkbox->setState(m_shader);

	m_gui.add(m_titleLabel);
	m_gui.add(m_backButton);
	m_gui.add(m_checkbox);
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

void DisplayOptions::checkboxCallback()
{
	m_shader = m_checkbox->getState();
}
