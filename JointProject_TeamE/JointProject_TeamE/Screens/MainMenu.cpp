#include "MainMenu.h"

MainMenu::MainMenu()
{
	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	// TODO(Darren): Take in screen width and height so i can do UI independent resolution
	m_raceButton = new Button(focusColor, nofocusColor, fillColor, "Race!", nullptr, 
		sf::Vector2f(400.0f, 50.0f), 18, 200.0f);
	m_upgradesButton = new Button(focusColor, nofocusColor, fillColor, "Upgrades", nullptr, 
		sf::Vector2f(400.0f, 150.0f), 18, 200.0f);
	m_trophiesButton = new Button(focusColor, nofocusColor, fillColor, "Trophies", nullptr, 
		sf::Vector2f(400.0f, 250.0f), 18, 200.0f);
	m_optionsButton = new Button(focusColor, nofocusColor, fillColor, "Options", nullptr, 
		sf::Vector2f(400.0f, 350.0f), 18, 200.0f);
	m_creditsButton = new Button(focusColor, nofocusColor, fillColor, "Credits", nullptr, 
		sf::Vector2f(400.0f, 450.0f), 18, 200.0f);
	m_exitButton = new Button(focusColor, nofocusColor, fillColor, "Exit", nullptr, 
		sf::Vector2f(400.0f, 550.0f), 18, 200.0f);

	m_raceButton->promoteFocus();

	m_raceButton->m_up = m_exitButton;
	m_raceButton->m_down = m_upgradesButton;
	m_upgradesButton->m_up = m_raceButton;
	m_upgradesButton->m_down = m_trophiesButton;
	m_trophiesButton->m_up = m_upgradesButton;
	m_trophiesButton->m_down = m_optionsButton;
	m_optionsButton->m_up = m_trophiesButton;
	m_optionsButton->m_down = m_creditsButton;
	m_creditsButton->m_up = m_optionsButton;
	m_creditsButton->m_down = m_exitButton;
	m_exitButton->m_up = m_creditsButton;
	m_exitButton->m_down = m_raceButton;

	m_screenGUI.add(m_raceButton);
	m_screenGUI.add(m_upgradesButton);
	m_screenGUI.add(m_trophiesButton);
	m_screenGUI.add(m_optionsButton);
	m_screenGUI.add(m_creditsButton);
	m_screenGUI.add(m_exitButton);
}

MainMenu::~MainMenu() { }

void MainMenu::update()
{
	m_screenGUI.update();
}

void MainMenu::render(sf::RenderWindow &window)
{
	window.draw(m_screenGUI);
}

void MainMenu::processInput(XboxController &controller)
{
	m_screenGUI.processInput(controller);
}