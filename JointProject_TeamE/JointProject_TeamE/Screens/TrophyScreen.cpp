#include "TrophyScreen.h"

/// <summary>
/// Initalises the trophy display
/// </summary>
TrophyScreen::TrophyScreen() 
	: Screen(GameState::TrophyScreen)
{
	m_trophyTexture = g_resourceMgr.textureHolder["Trophies"];

	m_trophyNames[0] = "Circuit de Monaco";
	m_trophyNames[1] = "Circuit Zolder";
	m_trophyNames[2] = "Circuito de Monsanto";

	for (int i = 0; i < 3; i++)
	{
		m_trophyUnlocked[i] = true;
		m_trophySprite[i].setTexture(m_trophyTexture);
		m_trophySprite[i].setTextureRect(sf::IntRect(i * 45, 0, 40, 76));
		m_trophyPosition[i] = sf::Vector2f(200.0f * (i + 1), 300.0f);
		m_trophySprite[i].setPosition(m_trophyPosition[i]);
		m_trophySprite[i].setOrigin(m_trophySprite[i].getLocalBounds().width / 2, m_trophySprite[i].getLocalBounds().height / 2);
	}

	m_transitionIn = true;

	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(1400.0f, 400.0f);

	m_titleLabel = new Label("Trophy Room", nullptr, 30.0f, sf::Vector2f(400.0f, 80.0f), endTranstionPos);
	m_titleLabel->setPosition(sf::Vector2f(900.0f, 80.0f));
	m_backButton = new Button(focusColor, nofocusColor, fillColor, "Back", nullptr, sf::Vector2f(900.0f, 500.0f),
		18, 100.0f, 40.0f, sf::Vector2f(400.0f, 500.0f), endTranstionPos);

	for (int i = 0; i < 3; i++)
	{
		m_trophyTitle[i] = new Label("???", nullptr, 18.0f, m_trophyPosition[i] + sf::Vector2f(20.0f, 50.0f), endTranstionPos);
		m_trophyTitle[i]->setPosition(m_trophyPosition[i] + sf::Vector2f(20.0f, 50.0f));
	}

	m_backButton->select = std::bind(&TrophyScreen::backButtonCallback, this);

	m_backButton->promoteFocus();

	m_gui.add(m_titleLabel);
	m_gui.add(m_backButton);
	for (int i = 0; i < 3; i++)
		m_gui.add(m_trophyTitle[i]);
}

TrophyScreen::~TrophyScreen() { }

/// <summary>
/// Updates the gui and process input
/// </summary>
/// <param name="controller">A refernce to a controller object</param>
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

/// <summary>
/// Renders the gui and trophies
/// </summary>
/// <param name="window"></param>
void TrophyScreen::render(sf::RenderWindow &window)
{
	window.draw(m_gui);

	for (int i = 0; i < 3; i++)
	{
		std::string name;
		m_trophyUnlocked[i] ? name = m_trophyNames[i] : name = "???";
		m_trophyTitle[i]->setText(name);

		if(m_trophyUnlocked[i])
			window.draw(m_trophySprite[i]);
		else
		{
			m_trophySprite[i].setColor(sf::Color::Red);
			window.draw(m_trophySprite[i]);
		}
	}
}

/// <summary>
/// Resets the screen
/// </summary>
void TrophyScreen::reset()
{
	m_backButtonSelected = false;
	m_interpolation = 0.f;
	m_transitionIn = true;
}

/// <summary>
/// Method to set a trophy to be unlocked
/// </summary>
/// <param name="trophyIndex">The trophy index</param>
void TrophyScreen::unlockTrophy(int trophyIndex)
{
	if (trophyIndex < 0 || trophyIndex >= 3)
	{
		std::cout << "TrophyScreen:: Trophy Index is out of bounds" << std::endl;
		return;
	}

	m_trophyUnlocked[trophyIndex] = true;
}

/// <summary>
/// Callback for the back button being pressed
/// </summary>
void TrophyScreen::backButtonCallback()
{
	m_backButtonSelected = true;
}