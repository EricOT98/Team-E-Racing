#include "Options.h"

Options::Options()
{
	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(-1400.0f, 400.0f);

	m_titleLabel = new Label("Options", nullptr, 30.0f, sf::Vector2f(400.0f, 80.0f), endTranstionPos);
	m_titleLabel->setPosition(sf::Vector2f(400.0f, 80.0f));
	m_soundButton = new Button(focusColor, nofocusColor, fillColor, "Sound", nullptr,
		sf::Vector2f(400.0f, 150.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 150.0f), endTranstionPos);
	m_displayButton = new Button(focusColor, nofocusColor, fillColor, "Display", nullptr,
		sf::Vector2f(400.0f, 250.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 250.0f), endTranstionPos);
	m_helpButton = new Button(focusColor, nofocusColor, fillColor, "Help", nullptr,
		sf::Vector2f(400.0f, 350.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 350.0f), endTranstionPos);
	m_difficultyButton = new Button(focusColor, nofocusColor, fillColor, "Difficulty", nullptr,
		sf::Vector2f(400.0f, 450.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 450.0f), endTranstionPos);
	m_backButton = new Button(focusColor, nofocusColor, fillColor, "Back", nullptr,
		sf::Vector2f(400.0f, 550.0f), 18, 200.0f, 40.0f, sf::Vector2f(400.0f, 550.0f), endTranstionPos);
	
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

	m_optionsGUI.add(m_titleLabel);
	m_optionsGUI.add(m_soundButton);
	m_optionsGUI.add(m_displayButton);
	m_optionsGUI.add(m_helpButton);
	m_optionsGUI.add(m_difficultyButton);
	m_optionsGUI.add(m_backButton);
}

Options::~Options()
{
	delete m_soundButton;
	delete m_displayButton;
	delete m_helpButton;
	delete m_difficultyButton;
	delete m_backButton;
}

void Options::update()
{
	m_optionsGUI.update();
}

void Options::render(sf::RenderWindow &window)
{
	window.draw(m_optionsGUI);
}

void Options::processInput(XboxController &controller)
{
	m_optionsGUI.processInput(controller);
}