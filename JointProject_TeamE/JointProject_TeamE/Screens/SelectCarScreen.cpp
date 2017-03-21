#include "SelectCarScreen.h"

SelectCarScreen::SelectCarScreen(std::vector<CarData> & carsIn, Player * playerIn, int screenWidth) : Screen(GameState::SelectCarScreen), m_player(playerIn), m_cars(carsIn)
{
	m_transitionIn = true;
	m_resetSliders = true;

	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(1400.0f, 400.0f);

	m_title = new Label("Select Car", nullptr, 50, sf::Vector2f(420.0f, 50.0f), endTranstionPos);
	m_title->setPosition(sf::Vector2f(-400.0f, 50.0f));
	m_backButton = new Button(focusColor, nofocusColor, fillColor, "Back", nullptr, sf::Vector2f(-320.0f, 350.0f),
		18, 100.0f, 40.0f, sf::Vector2f(320.0f, 430.0f), endTranstionPos);
	m_confirmButton = new Button(focusColor, nofocusColor, fillColor, "Confirm", nullptr, sf::Vector2f(-320.0f, 350.0f),
		18, 100.0f, 40.0f, sf::Vector2f(520.0f, 430.0f), endTranstionPos);
	m_accelerationSlider = new Slider(focusColor, nofocusColor, fillColor, "Acceleration", nullptr, sf::Vector2f(400.0f, -200.0f),
		18, 250.0f, 15.0f, sf::Vector2f(420.0f, 250.0f), endTranstionPos);
	m_brakingSlider = new Slider(focusColor, nofocusColor, fillColor, "Braking", nullptr, sf::Vector2f(400.0f, -200.0f),
		18, 250.0f, 15.0f, sf::Vector2f(420.0f, 300.0f), endTranstionPos);
	m_corneringSlider = new Slider(focusColor, nofocusColor, fillColor, "Cornering", nullptr, sf::Vector2f(400.0f, -200.0f),
		18, 250.0f, 15.0f, sf::Vector2f(420.0f, 350.0f), endTranstionPos);
	int baseXPos = (screenWidth / (m_cars.size() + 1));
	for (int i = 0; i < m_cars.size(); i++)
	{
		int xPos = baseXPos * (i + 1) + 15;
		RadioButton * rad = new RadioButton(focusColor, nofocusColor, fillColor, m_cars.at(i).m_name, nullptr,
			endTranstionPos, m_radButtons, sf::Vector2f(xPos, 150.0f), endTranstionPos,
			22, 30.0f, 30.0f);
		rad->select = std::bind(&SelectCarScreen::radButtonCallback, this);
		m_radButtons.push_back(rad);
		m_gui.add(rad);
	}
	for (int i = 0; i < m_cars.size(); i++)
	{
		if (i > 0)
			m_radButtons.at(i)->m_left = m_radButtons.at((i - 1) % m_cars.size());
		if (i < m_cars.size() - 1)
			m_radButtons.at(i)->m_right = m_radButtons.at((i + 1) % m_cars.size());
		m_radButtons.at(i)->m_down = m_confirmButton;
		m_radButtons.at(i)->m_up = m_confirmButton;
	}
	m_radButtons.at(0)->activate();
	m_currentCarIndex = 0;
	setSliders();

	m_confirmButton->m_left = m_backButton;
	m_confirmButton->m_right = m_backButton;
	m_confirmButton->m_up = m_radButtons.at(0);
	m_confirmButton->m_down = m_radButtons.at(0);
	m_backButton->m_left = m_confirmButton;
	m_backButton->m_right = m_confirmButton;
	m_backButton->m_up = m_radButtons.at(0);
	m_backButton->m_down = m_radButtons.at(0);

	m_confirmButton->select = std::bind(&SelectCarScreen::confirmButtonCallback, this);
	m_backButton->select = std::bind(&SelectCarScreen::backButtonCallback, this);

	m_gui.add(m_confirmButton);
	m_gui.add(m_backButton);
	m_gui.add(m_accelerationSlider);
	m_gui.add(m_brakingSlider);
	m_gui.add(m_corneringSlider);

	m_confirmButton->promoteFocus();
}

SelectCarScreen::~SelectCarScreen() {}

void SelectCarScreen::update(XboxController & controller)
{
	if (m_transitionIn)
	{
		if (m_resetSliders)
		{
			setSliders();
			m_resetSliders = false;
		}
		m_gui.transitionIn(0.03f, m_interpolation);

		if (m_interpolation >= 1.0f)
		{
			m_transitionIn = false;
			m_interpolation = 0.0f;
		}
	}
	else if (m_confirmButtonPressed)
	{
		transOut(GameState::SelectCupScreen);
	}
	else if (m_backButtonPressed)
	{
		transOut(GameState::MainMenu);
	}
	m_gui.processInput(controller);
}

void SelectCarScreen::reset()
{
	m_interpolation = 0.f;
	m_transitionIn = true;
	m_backButtonPressed = false;
	m_confirmButtonPressed = false;
	m_resetSliders = true;
}

void SelectCarScreen::confirmButtonCallback()
{
	m_confirmButtonPressed = true;
	m_player->setCar(m_cars.at(m_currentCarIndex));
}

void SelectCarScreen::backButtonCallback()
{
	m_backButtonPressed = true;
}

void SelectCarScreen::radButtonCallback()
{
	for (int i = 0; i < m_radButtons.size(); i++)
	{
		if (m_radButtons.at(i)->getState())
		{
			m_currentCarIndex = i;
		}
	}
	setSliders();
}

void SelectCarScreen::setSliders()
{
	m_accelerationSlider->setPercentageFull(m_cars.at(m_currentCarIndex).m_acceleration / 300.f);
	m_brakingSlider->setPercentageFull(m_cars.at(m_currentCarIndex).m_deceleration / 300.f);
	m_corneringSlider->setPercentageFull(m_cars.at(m_currentCarIndex).m_turnRate / 300.f);
}
