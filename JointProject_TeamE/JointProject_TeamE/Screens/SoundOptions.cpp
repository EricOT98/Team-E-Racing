#include "SoundOptions.h"

SoundOptions::SoundOptions()
{
	m_transitionIn = true;
	m_transitionOut = false;

	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(400.0f, -1400.0f);

	m_titleLabel = new Label("Options", nullptr, 30.0f, sf::Vector2f(400.0f, 80.0f), endTranstionPos);
	m_titleLabel->setPosition(sf::Vector2f(400.0f, -80.0f));
	m_musicSlider = new Slider(focusColor, nofocusColor, fillColor, "Music Volume", nullptr, sf::Vector2f(400.0f, -200.0f),
		18, 250.0f, 15.0f, sf::Vector2f(400.0f, 200.0f), endTranstionPos);
	m_effectSlider = new Slider(focusColor, nofocusColor, fillColor, "Effects Volume", nullptr, sf::Vector2f(400.0f, -300.0f),
		18, 250.0f, 15.0f, sf::Vector2f(400.0f, 300.0f), endTranstionPos);
	m_muteCheckBox = new CheckBox(focusColor, nofocusColor, fillColor, "Mute", nullptr, sf::Vector2f(400.0f, -400.0f),
		22, 40.0f, 40.0f, sf::Vector2f(400.0f, 400.0f), endTranstionPos);
	m_backButton = new Button(focusColor, nofocusColor, fillColor, "Back", nullptr, sf::Vector2f(400.0f, -500.0f),
		18, 200.0f, 40.0f, sf::Vector2f(400.0f, 500.0f), endTranstionPos);

	m_musicSlider->promoteFocus();

	m_musicSlider->m_up = m_backButton;
	m_musicSlider->m_down = m_effectSlider;
	m_effectSlider->m_up = m_musicSlider;
	m_effectSlider->m_down = m_muteCheckBox;
	m_muteCheckBox->m_up = m_effectSlider;
	m_muteCheckBox->m_down = m_backButton;
	m_backButton->m_up = m_muteCheckBox;
	m_backButton->m_down = m_musicSlider;

	m_soundOpitionsGUI.add(m_titleLabel);
	m_soundOpitionsGUI.add(m_musicSlider);
	m_soundOpitionsGUI.add(m_effectSlider);
	m_soundOpitionsGUI.add(m_muteCheckBox);
	m_soundOpitionsGUI.add(m_backButton);
}

SoundOptions::~SoundOptions() { }

void SoundOptions::update()
{
	if (m_transitionIn)
	{
		m_soundOpitionsGUI.transitionIn(0.03f, m_interpolation);

		if (m_interpolation >= 1.0f)
		{
			m_transitionIn = false;
			m_interpolation = 0.0f;
		}
	}

	checkScreenTransition(m_backButton, GameScreenState::OptionsScreen);

	m_soundOpitionsGUI.update();
}

void SoundOptions::checkScreenTransition(Button *button, GameScreenState stateToChangeTo)
{
	if (button->pressed && button->getFocus())
	{
		m_soundOpitionsGUI.transitionOut(0.03f, m_interpolation);

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

void SoundOptions::render(sf::RenderWindow &window)
{
	window.draw(m_soundOpitionsGUI);
}

void SoundOptions::processInput(XboxController &controller)
{
	m_soundOpitionsGUI.processInput(controller);
}