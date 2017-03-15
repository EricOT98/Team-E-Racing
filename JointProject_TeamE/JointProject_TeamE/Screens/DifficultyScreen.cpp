#include "DifficultyScreen.h"

/// <summary>
/// Initalises the widgets in the scene and add them to the widget manager
/// </summary>
DifficultyScreen::DifficultyScreen() : Screen(GameState::DifficultyScreen)
{
	m_transitionIn = true;

	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(400.0f, 1400.0f);

	m_difficultyLabel = new Label("Difficulty", nullptr, 50, sf::Vector2f(400.0f, 50.0f), endTranstionPos);
	m_difficultyLabel->setPosition(sf::Vector2f(-400.0f, 50.0f));
	m_numOfOppLabel = new Label("Number of Opponents", nullptr, 30, sf::Vector2f(400.0f, 200.0f), endTranstionPos);
	m_numOfOppLabel->setPosition(sf::Vector2f(-400.0f, 200.0f));
	m_radioButtons.push_back(new RadioButton(focusColor, nofocusColor, fillColor, "3", nullptr,
		endTranstionPos, m_radioButtons, sf::Vector2f(290.0f, 300.0f), endTranstionPos,
		22, 30.0f, 30.0f));
	m_radioButtons.push_back(new RadioButton(focusColor, nofocusColor, fillColor, "4", nullptr,
		endTranstionPos, m_radioButtons, sf::Vector2f(360.0f, 300.0f), endTranstionPos,
		22, 30.0f, 30.0f));
	m_radioButtons.push_back(new RadioButton(focusColor, nofocusColor, fillColor, "5", nullptr,
		endTranstionPos, m_radioButtons, sf::Vector2f(440.0f, 300.0f), endTranstionPos,
		22, 30.0f, 30.0f));
	m_radioButtons.push_back(new RadioButton(focusColor, nofocusColor, fillColor, "6", nullptr,
		endTranstionPos, m_radioButtons, sf::Vector2f(520.0f, 300.0f), endTranstionPos,
		22, 30.0f, 30.0f));
	m_backButton = new Button(focusColor, nofocusColor, fillColor, "Back", nullptr,
		endTranstionPos, 18, 100.0f, 40.0f, sf::Vector2f(400.0f, 400.0f), endTranstionPos);

	m_radioButtons.at(0)->promoteFocus();

	m_radioButtons.at(0)->m_left = m_radioButtons.at(3);
	m_radioButtons.at(0)->m_right = m_radioButtons.at(1);
	m_radioButtons.at(1)->m_left = m_radioButtons.at(0);
	m_radioButtons.at(1)->m_right = m_radioButtons.at(2);
	m_radioButtons.at(2)->m_left = m_radioButtons.at(1);
	m_radioButtons.at(2)->m_right = m_radioButtons.at(3);
	m_radioButtons.at(3)->m_left = m_radioButtons.at(2);
	m_radioButtons.at(3)->m_right = m_radioButtons.at(0);

	for (RadioButton *radioButton : m_radioButtons)
	{
		radioButton->m_down = m_backButton;
		radioButton->select = std::bind(&DifficultyScreen::radioButtonSetCallback, this);
	}
	m_backButton->m_up = m_radioButtons.at(0);

	m_backButton->select = std::bind(&DifficultyScreen::backButtonCallback, this);

	m_gui.add(m_difficultyLabel);
	m_gui.add(m_numOfOppLabel);
	for (RadioButton *radioButton : m_radioButtons)
		m_gui.add(radioButton);
	m_gui.add(m_backButton);
}

DifficultyScreen::~DifficultyScreen()
{
	m_gui.clear();
}

/// <summary>
/// Update the widgets contatined in the difficulty screen manager
/// </summary>
void DifficultyScreen::update(XboxController & controller)
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

void DifficultyScreen::reset()
{
	m_backButtonSelected = false;
	m_transitionIn = true;
	m_interpolation = 0.f;
}

void DifficultyScreen::backButtonCallback()
{
	m_backButtonSelected = true;
}

void DifficultyScreen::radioButtonSetCallback()
{
	// Insert Code Here
}