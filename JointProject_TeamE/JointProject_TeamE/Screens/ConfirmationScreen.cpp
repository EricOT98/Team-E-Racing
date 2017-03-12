#include "ConfirmationScreen.h"

ConfirmationScreen::ConfirmationScreen()
{
	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(1400.0f, 400.0f);

	m_confirmationLabel = new Label("Confirmation", nullptr, 50, sf::Vector2f(400.0f, 50.0f), endTranstionPos);
	m_areYouSureLabel = new Label("Are you sure?", nullptr, 30, sf::Vector2f(400.0f, 250.0f), endTranstionPos);
	m_yesButton = new Button(focusColor, nofocusColor, fillColor, "Yes", nullptr, sf::Vector2f(320.0f, 350.0f), 
		18, 100.0f, 40.0f, sf::Vector2f(320.0f, 350.0f), endTranstionPos);
	m_noButton = new Button(focusColor, nofocusColor, fillColor, "No", nullptr, sf::Vector2f(480.0f, 350.0f),
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
	m_confirmationScreenGUI.update();
}

void ConfirmationScreen::render(sf::RenderWindow &window)
{
	window.draw(m_confirmationScreenGUI);
}

void ConfirmationScreen::processInput(XboxController &controler)
{
	m_confirmationScreenGUI.processInput(controler);
}