//#include "DisplayOptions.h"
//
//DisplayOptions::DisplayOptions()
//{
//	m_transitionIn = true;
//	m_transitionOut = false;
//
//	sf::Color focusColor = sf::Color::Red;
//	sf::Color nofocusColor = sf::Color::Magenta;
//	sf::Color fillColor = sf::Color::Blue;
//
//	sf::Vector2f endTranstionPos = sf::Vector2f(900.0f, 900.0f);
//
//	m_titleLabel = new Label("Display Opitions", nullptr, 50,
//		sf::Vector2f(400.0f, 50.0f), endTranstionPos);
//	m_titleLabel->setPosition(endTranstionPos);
//
//	m_backButton = new Button(focusColor, nofocusColor, fillColor, "Back", nullptr, 
//		sf::Vector2f(-500.0f, -400.0f), 18, 100.0f, 40.0f, sf::Vector2f(400.0f, 500.0f), endTranstionPos);
//
//	m_backButton->promoteFocus();
//
//	m_displayOpitionsGUI.add(m_titleLabel);
//	m_displayOpitionsGUI.add(m_backButton);
//}
//
//DisplayOptions::~DisplayOptions() { }
//
//void DisplayOptions::update()
//{
//	if (m_transitionIn)
//	{
//		m_displayOpitionsGUI.transitionIn(0.03f, m_interpolation);
//
//		if (m_interpolation >= 1.0f)
//		{
//			m_transitionIn = false;
//			m_interpolation = 0.0f;
//		}
//	}
//
//	checkScreenTransition(m_backButton, GameScreenState::OptionsScreen);
//
//	m_displayOpitionsGUI.update();
//}
//
//void DisplayOptions::render(sf::RenderWindow &window)
//{
//	window.draw(m_displayOpitionsGUI);
//}
//
//void DisplayOptions::processInput(XboxController &controller)
//{
//	m_displayOpitionsGUI.processInput(controller);
//}
//
//void DisplayOptions::checkScreenTransition(Button *button, GameScreenState stateToChangeTo)
//{
//	if (button->pressed && button->getFocus())
//	{
//		m_displayOpitionsGUI.transitionOut(0.03f, m_interpolation);
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