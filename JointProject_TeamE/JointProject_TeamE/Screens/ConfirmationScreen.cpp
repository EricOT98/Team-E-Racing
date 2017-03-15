#include "ConfirmationScreen.h"

ConfirmationScreen::ConfirmationScreen() : Screen(GameState::QuitScreen)
{
	m_transitionIn = true;

	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(1400.0f, 400.0f);

	m_confirmationLabel = new Label("Confirmation", nullptr, 50, sf::Vector2f(400.0f, 50.0f), endTranstionPos);
	m_confirmationLabel->setPosition(sf::Vector2f(-400.0f, 50.0f));
	m_areYouSureLabel = new Label("Are you sure?", nullptr, 30, sf::Vector2f(400.0f, 250.0f), endTranstionPos);
	m_areYouSureLabel->setPosition(sf::Vector2f(-400.0f, 250.0f));
	m_yesButton = new Button(focusColor, nofocusColor, fillColor, "Yes", nullptr, sf::Vector2f(-320.0f, 350.0f), 
		18, 100.0f, 40.0f, sf::Vector2f(320.0f, 350.0f), endTranstionPos);
	m_noButton = new Button(focusColor, nofocusColor, fillColor, "No", nullptr, sf::Vector2f(-480.0f, 350.0f),
		18, 100.0f, 40.0f, sf::Vector2f(480.0f, 350.0f), endTranstionPos);

	m_yesButton->promoteFocus();

	m_yesButton->m_right = m_noButton;
	m_noButton->m_left = m_yesButton;

	m_yesButton->select = std::bind(&ConfirmationScreen::yesButtonCallback, this);
	m_noButton->select = std::bind(&ConfirmationScreen::noButtonCallback, this);

	m_gui.add(m_confirmationLabel);
	m_gui.add(m_areYouSureLabel);
	m_gui.add(m_yesButton);
	m_gui.add(m_noButton);

	m_gui.update();
}

ConfirmationScreen::~ConfirmationScreen() { }

void ConfirmationScreen::update(XboxController & controller)
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
	else if (m_noButtonSelected)
	{
		transOut(GameState::MainMenu);
	}
	m_gui.processInput(controller);
}

void ConfirmationScreen::reset()
{
	m_transitionIn = true;
	m_interpolation = 0.f;
	m_noButtonSelected = false;
}

void ConfirmationScreen::yesButtonCallback()
{
	// Code to end the game
}

void ConfirmationScreen::noButtonCallback()
{
	m_noButtonSelected = true;
}