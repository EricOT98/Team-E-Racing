#include "DifficultyScreen.h"

/// <summary>
/// Initalises the widgets in the scene and add them to the widget manager
/// </summary>
DifficultyScreen::DifficultyScreen()
{
	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(400.0f, 1400.0f);

	m_difficultyLabel = new Label("Diffiuclty", nullptr, 50, sf::Vector2f(400.0f, 50.0f), endTranstionPos);
	m_difficultyLabel->setPosition(sf::Vector2f(400.0f, 50.0f));
	m_numOfOppLabel = new Label("Number of Opponents", nullptr, 30, sf::Vector2f(400.0f, 200.0f), endTranstionPos);
	m_numOfOppLabel->setPosition(sf::Vector2f(400.0f, 200.0f));
	m_radioButtons.push_back(new RadioButton(focusColor, nofocusColor, fillColor, "3", nullptr,
		sf::Vector2f(310.0f, 280.0f), m_radioButtons, sf::Vector2f(350.0f, 180.0f), endTranstionPos,
		22, 30.0f, 30.0f));
	m_radioButtons.push_back(new RadioButton(focusColor, nofocusColor, fillColor, "4", nullptr,
		sf::Vector2f(370.0f, 280.0f), m_radioButtons, sf::Vector2f(380.0f, 180.0f), endTranstionPos,
		22, 30.0f, 30.0f));
	m_radioButtons.push_back(new RadioButton(focusColor, nofocusColor, fillColor, "5", nullptr,
		sf::Vector2f(430.0f, 280.0f), m_radioButtons, sf::Vector2f(400.0f, 180.0f), endTranstionPos,
		22, 30.0f, 30.0f));
	m_radioButtons.push_back(new RadioButton(focusColor, nofocusColor, fillColor, "6", nullptr,
		sf::Vector2f(490.0f, 280.0f), m_radioButtons, sf::Vector2f(420.0f, 180.0f), endTranstionPos,
		22, 30.0f, 30.0f));
	m_backButton = new Button(focusColor, nofocusColor, fillColor, "Back", nullptr,
		sf::Vector2f(400.0f, 400.0f), 18, 100.0f, 40.0f, sf::Vector2f(400.0f, 400.0f), endTranstionPos);

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
		radioButton->m_down = m_backButton;

	m_backButton->m_up = m_radioButtons.at(0);

	m_difficultyScreenGUI.add(m_difficultyLabel);
	m_difficultyScreenGUI.add(m_numOfOppLabel);
	for (RadioButton *radioButton : m_radioButtons)
		m_difficultyScreenGUI.add(radioButton);
	m_difficultyScreenGUI.add(m_backButton);
}

DifficultyScreen::~DifficultyScreen()
{

}

/// <summary>
/// Update the widgets contatined in the difficulty screen manager
/// </summary>
void DifficultyScreen::update()
{
	m_difficultyScreenGUI.update();
}

/// <summary>
/// Render all the widgets
/// </summary>
/// <param name="window">A reference to the render window</param>
void DifficultyScreen::render(sf::RenderWindow &window)
{
	window.draw(m_difficultyScreenGUI);
}

/// <summary>
/// Process all the input for the widgets
/// </summary>
/// <param name="controller">A reference to the xbox controller</param>
void DifficultyScreen::processInput(XboxController &controller)
{
	m_difficultyScreenGUI.processInput(controller);
}