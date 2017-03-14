//#include "TrophyScreen.h"
//
//TrophyScreen::TrophyScreen()
//{
//	m_transitionOut = false;
//	m_transitionIn = true;
//
//	sf::Color focusColor = sf::Color::Red;
//	sf::Color nofocusColor = sf::Color::Magenta;
//	sf::Color fillColor = sf::Color::Blue;
//
//	sf::Vector2f endTranstionPos = sf::Vector2f(1400.0f, 400.0f);
//
//	m_titleLabel = new Label("Trophy Room", nullptr, 30.0f, sf::Vector2f(400.0f, 80.0f), endTranstionPos);
//	m_titleLabel->setPosition(sf::Vector2f(900.0f, 80.0f));
//	m_backButton = new Button(focusColor, nofocusColor, fillColor, "Back", nullptr, sf::Vector2f(900.0f, 500.0f),
//		18, 100.0f, 40.0f, sf::Vector2f(400.0f, 500.0f), endTranstionPos);
//
//	m_backButton->promoteFocus();
//
//	m_trophyScreenGUI.add(m_titleLabel);
//	m_trophyScreenGUI.add(m_backButton);
//}
//
//TrophyScreen::~TrophyScreen() { }
//
//void TrophyScreen::update()
//{
//	if (m_transitionIn)
//	{
//		m_trophyScreenGUI.transitionIn(0.03f, m_interpolation);
//
//		if (m_interpolation >= 1.0f)
//		{
//			m_transitionIn = false;
//			m_interpolation = 0.0f;
//		}
//	}
//
//	checkScreenTransition(m_backButton, GameScreenState::MainMenuScreen);
//
//	m_trophyScreenGUI.update();
//}
//
//void TrophyScreen::checkScreenTransition(Button *button, GameScreenState stateToChangeTo)
//{
//	if (button->pressed && button->getFocus())
//	{
//		m_trophyScreenGUI.transitionOut(0.03f, m_interpolation);
//
//		if (m_interpolation >= 1.0f)
//		{
//			m_interpolation = 0.0f;
//			currentGameState = stateToChangeTo;
//			m_transitionOut = false;
//			m_transitionIn = true;
//			button->pressed = false;
//		}
//	}
//}
//
//void TrophyScreen::render(sf::RenderWindow &window)
//{
//	window.draw(m_trophyScreenGUI);
//}
//
//void TrophyScreen::processInput(XboxController &controller)
//{
//	m_trophyScreenGUI.processInput(controller);
//}