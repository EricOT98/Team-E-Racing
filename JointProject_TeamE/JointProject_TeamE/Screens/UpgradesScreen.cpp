#include "UpgradesScreen.h"

UpgradesScreen::UpgradesScreen() : Screen(GameState::UpgradesScreen), m_backButtonPressed(false)
{
	m_transitionIn = true;

	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(1400.0f, 400.0f);

	m_title = new Label("Upgrades", nullptr, 50, sf::Vector2f(420.0f, 50.0f), endTranstionPos);
	m_title->setPosition(sf::Vector2f(-400.0f, 50.0f));
	m_accelerationButton = new Button(focusColor, nofocusColor, fillColor, "Acceleration", nullptr, sf::Vector2f(-320.0f, 350.0f),
		18, 100.0f, 40.0f, sf::Vector2f(220.0f, 430.0f), endTranstionPos);
	m_brakingButton = new Button(focusColor, nofocusColor, fillColor, "Braking", nullptr, sf::Vector2f(-320.0f, 350.0f),
		18, 100.0f, 40.0f, sf::Vector2f(420.0f, 430.0f), endTranstionPos);
	m_corneringButton = new Button(focusColor, nofocusColor, fillColor, "Cornering", nullptr, sf::Vector2f(-320.0f, 350.0f),
		18, 100.0f, 40.0f, sf::Vector2f(620.0f, 430.0f), endTranstionPos);
	m_backButton = new Button(focusColor, nofocusColor, fillColor, "Back", nullptr, sf::Vector2f(-320.0f, 350.0f),
		18, 100.0f, 40.0f, sf::Vector2f(420.0f, 500.0f), endTranstionPos);

	m_accelerationButton->promoteFocus();

	m_accelerationButton->m_right = m_brakingButton;
	m_accelerationButton->m_left = m_corneringButton;
	m_accelerationButton->m_down = m_backButton;
	m_brakingButton->m_right = m_corneringButton;
	m_brakingButton->m_left = m_accelerationButton;
	m_brakingButton->m_down = m_backButton;
	m_corneringButton->m_right = m_accelerationButton;
	m_corneringButton->m_left = m_brakingButton;
	m_corneringButton->m_down = m_backButton;
	m_backButton->m_up = m_accelerationButton;

	m_backButton->select = std::bind(&UpgradesScreen::backCallback, this);

	m_gui.add(m_title);
	m_gui.add(m_accelerationButton);
	m_gui.add(m_brakingButton);
	m_gui.add(m_corneringButton);
	m_gui.add(m_backButton);

	m_gui.update();
}

UpgradesScreen::~UpgradesScreen() {}

void UpgradesScreen::update(XboxController & controller)
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
	else if (m_backButtonPressed)
	{
		transOut(GameState::MainMenu);
	}
	m_gui.processInput(controller);
}

void UpgradesScreen::reset()
{
	m_backButtonPressed = false;
	m_transitionIn = true;
	m_interpolation = 0.f;
}

void UpgradesScreen::render(sf::RenderWindow& window)
{
	window.draw(m_gui);
}

void UpgradesScreen::backCallback()
{
	m_backButtonPressed = true;
}