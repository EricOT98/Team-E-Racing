#include "TrophyScreen.h"

TrophyScreen::TrophyScreen() : Screen(GameState::TrophyScreen)
{
	m_transitionIn = true;

	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(1400.0f, 400.0f);

	m_titleLabel = new Label("Trophy Room", nullptr, 30.0f, sf::Vector2f(400.0f, 80.0f), endTranstionPos);
	m_titleLabel->setPosition(sf::Vector2f(900.0f, 80.0f));
	m_backButton = new Button(focusColor, nofocusColor, fillColor, "Back", nullptr, sf::Vector2f(900.0f, 500.0f),
		18, 100.0f, 40.0f, sf::Vector2f(400.0f, 500.0f), endTranstionPos);

	m_backButton->select = std::bind(&TrophyScreen::backButtonCallback, this);

	m_backButton->promoteFocus();

	m_gui.add(m_titleLabel);
	m_gui.add(m_backButton);

	// Set the textures of the spriytes using the resource manager
}

TrophyScreen::~TrophyScreen() { }

void TrophyScreen::update(XboxController & controller)
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
	m_gui.processInput(controller);
}

void TrophyScreen::render(sf::RenderWindow &window)
{
	window.draw(m_gui);
	window.draw(m_trophySprite1);
	window.draw(m_trophySprite2);
	window.draw(m_trophySprite3);
}

void TrophyScreen::reset()
{
	m_backButtonSelected = false;
	m_interpolation = 0.f;
	m_transitionIn = true;
}

void TrophyScreen::backButtonCallback()
{
	m_backButtonSelected = true;
}