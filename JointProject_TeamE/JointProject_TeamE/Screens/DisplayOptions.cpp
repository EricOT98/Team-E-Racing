#include "DisplayOptions.h"

/// <summary>
/// The default constructor for the display options screen.
/// This constructor in a reference to a boolean value that is applied to the function
/// call back of the checkbox.
/// This is to allow the display options to toggle the passed in boolean value via 
/// a checkbox
/// </summary>
/// <param name="shaderIn">Reference to a boolean that controls whether the shader will be drawn</param>
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

/// <summary>
/// Update the transition positions of the screen if it is not already in position/
/// else process input for the gui objects
/// </summary>
/// <param name="controller">Current connected Xbox360 controller</param>
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

/// <summary>
/// Reset the current screen
/// </summary>
void DisplayOptions::reset()
{
	m_transitionIn = true;
	m_interpolation = 0.f;
	m_backButtonSelected = false;
}

/// <summary>
/// Callback function for the selection of the back button to change
/// the bool value in the menu.
/// </summary>
void DisplayOptions::backButtonCallback()
{
	m_backButtonSelected = true;
}

/// <summary>
/// Callback function to set the reference shader to the current checkbox state
/// </summary>
void DisplayOptions::checkboxCallback()
{
	m_shader = m_checkbox->getState();
}
