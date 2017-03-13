#include "ConfirmationScreen.h"

ConfirmationScreen::ConfirmationScreen()
{
	m_transitionOut = false;
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

	m_confirmationScreenGUI.add(m_confirmationLabel);
	m_confirmationScreenGUI.add(m_areYouSureLabel);
	m_confirmationScreenGUI.add(m_yesButton);
	m_confirmationScreenGUI.add(m_noButton);
}

ConfirmationScreen::~ConfirmationScreen() { }

void ConfirmationScreen::update()
{
	if (m_transitionIn)
	{
		m_confirmationScreenGUI.transitionIn(0.03f, m_interpolation);

		if (m_interpolation >= 1.0f)
		{
			m_transitionIn = false;
			m_interpolation = 0.0f;
		}
	}

	checkScreenTransition(m_yesButton, GameScreenState::QuitGame);
	checkScreenTransition(m_noButton, GameScreenState::MainMenuScreen);

	m_confirmationScreenGUI.update();
}

void ConfirmationScreen::checkScreenTransition(Button *button, GameScreenState stateToChangeTo)
{
	if (button->pressed && button->getFocus())
	{
		m_confirmationScreenGUI.transitionOut(0.03f, m_interpolation);

		if (m_interpolation >= 1.0f)
		{
			m_interpolation = 0.0f;
			currentGameState = stateToChangeTo;
			m_transitionOut = false;
			m_transitionIn = true;
			button->pressed = false;
		}
	}
}

void ConfirmationScreen::render(sf::RenderWindow &window)
{
	window.draw(m_confirmationScreenGUI);
}

void ConfirmationScreen::processInput(XboxController &controler)
{
	m_confirmationScreenGUI.processInput(controler);
}