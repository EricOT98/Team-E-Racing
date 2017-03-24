#include "SoundOptions.h"

/// <summary>
/// Default constructor for the sound objects screen
/// </summary>
SoundOptions::SoundOptions() : Screen(GameState::SoundOptions)
{
	m_transitionIn = true;

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

	m_backButton->select = std::bind(&SoundOptions::backButtonCallback, this);
	m_muteCheckBox->select = std::bind(&SoundOptions::muteCallback, this);
	m_musicSlider->increase = std::bind(&SoundOptions::musicSliderCallback, this);
	m_musicSlider->decrease = std::bind(&SoundOptions::musicSliderCallback, this);
	m_effectSlider->increase = std::bind(&SoundOptions::effectsSliderCallback, this);
	m_effectSlider->decrease = std::bind(&SoundOptions::effectsSliderCallback, this);

	m_gui.add(m_titleLabel);
	m_gui.add(m_musicSlider);
	m_gui.add(m_effectSlider);
	m_gui.add(m_muteCheckBox);
	m_gui.add(m_backButton);
}

SoundOptions::~SoundOptions() { }

/// <summary>
/// if not transitioning process all gui objects
/// </summary>
/// <param name="controller"></param>
void SoundOptions::update(XboxController & controller)
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
		transOut(GameState::OptionsScreen);
	}
	m_gui.processInput(controller);
}

/// <summary>
/// reset the current screen
/// </summary>
void SoundOptions::reset()
{
	m_interpolation = 0.f;
	m_transitionIn = true;
	m_backButtonSelected = false;
}
//callback functions
void SoundOptions::backButtonCallback()
{
	m_backButtonSelected = true;
}

void SoundOptions::musicSliderCallback()
{
	// Code here ...
}

void SoundOptions::effectsSliderCallback()
{
	// Code here ...
}

void SoundOptions::muteCallback()
{
	// Code here ..
}