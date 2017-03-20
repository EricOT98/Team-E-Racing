#include "UpgradesScreen.h"

UpgradesScreen::UpgradesScreen(std::vector<CarData> & carsIn, int screenWidth) : Screen(GameState::UpgradesScreen), m_backButtonPressed(false), m_cars(carsIn), m_currentCarIndex(0)
{
	m_transitionIn = true;

	sf::Color focusColor = sf::Color::Red;
	sf::Color nofocusColor = sf::Color::Magenta;
	sf::Color fillColor = sf::Color::Blue;

	sf::Vector2f endTranstionPos = sf::Vector2f(1400.0f, 400.0f);

	m_title = new Label("Upgrades", nullptr, 50, sf::Vector2f(420.0f, 50.0f), endTranstionPos);
	m_title->setPosition(sf::Vector2f(-400.0f, 50.0f));
	m_accelerationButton = new Button(focusColor, nofocusColor, fillColor, "Acceleration", nullptr, sf::Vector2f(-320.0f, 350.0f),
		18, 100.0f, 40.0f, sf::Vector2f(220.0f, 430.0f), endTranstionPos);
	m_brakingButton = new Button(focusColor, nofocusColor, fillColor, "Braking", nullptr, sf::Vector2f(-320.0f, 350.0f),
		18, 100.0f, 40.0f, sf::Vector2f(420.0f, 430.0f), endTranstionPos);
	m_corneringButton = new Button(focusColor, nofocusColor, fillColor, "Cornering", nullptr, sf::Vector2f(-320.0f, 350.0f),
		18, 100.0f, 40.0f, sf::Vector2f(620.0f, 430.0f), endTranstionPos);
	m_backButton = new Button(focusColor, nofocusColor, fillColor, "Back", nullptr, sf::Vector2f(-320.0f, 350.0f),
		18, 100.0f, 40.0f, sf::Vector2f(420.0f, 500.0f), endTranstionPos);
	m_accelerationSlider = new Slider(focusColor, nofocusColor, fillColor, "Acceleration", nullptr, sf::Vector2f(400.0f, -200.0f),
		18, 250.0f, 15.0f, sf::Vector2f(650.0f, 150.0f), endTranstionPos);
	m_brakingSlider = new Slider(focusColor, nofocusColor, fillColor, "Braking", nullptr, sf::Vector2f(400.0f, -200.0f),
		18, 250.0f, 15.0f, sf::Vector2f(650.0f, 200.0f), endTranstionPos);
	m_corneringSlider = new Slider(focusColor, nofocusColor, fillColor, "Cornering", nullptr, sf::Vector2f(400.0f, -200.0f),
		18, 250.0f, 15.0f, sf::Vector2f(650.0f, 250.0f), endTranstionPos);
	int baseXPos = (screenWidth / (m_cars.size() + 1));
	for (int i = 0; i < m_cars.size(); i++)
	{
		int xPos = baseXPos * (i + 1) + 15;
		RadioButton * rad = new RadioButton(focusColor, nofocusColor, fillColor, m_cars.at(i).m_name, nullptr,
			endTranstionPos, m_radButtons, sf::Vector2f(xPos, 350.0f), endTranstionPos,
			22, 30.0f, 30.0f);
		rad->select = std::bind(&UpgradesScreen::radButtonCallback, this);
		m_radButtons.push_back(rad);
		m_gui.add(rad);
	}
	for (int i = 0; i < m_cars.size(); i++)
	{
		if(i > 0)
		m_radButtons.at(i)->m_left = m_radButtons.at((i - 1) % m_cars.size());
		if(i < m_cars.size() - 1)
		m_radButtons.at(i)->m_right = m_radButtons.at((i + 1) % m_cars.size());
		m_radButtons.at(i)->m_down = m_accelerationButton;
		m_radButtons.at(i)->m_up = m_backButton;
	}
	m_radButtons.at(0)->activate(); // Always have a radiobutton activated

	m_accelerationButton->promoteFocus();

	m_accelerationButton->m_up = m_radButtons.at(0);
	m_accelerationButton->m_right = m_brakingButton;
	m_accelerationButton->m_left = m_corneringButton;
	m_accelerationButton->m_down = m_backButton;
	m_brakingButton->m_right = m_corneringButton;
	m_brakingButton->m_left = m_accelerationButton;
	m_brakingButton->m_down = m_backButton;
	m_brakingButton->m_up = m_radButtons.at(0);
	m_corneringButton->m_right = m_accelerationButton;
	m_corneringButton->m_left = m_brakingButton;
	m_corneringButton->m_down = m_backButton;
	m_corneringButton->m_up = m_radButtons.at(0);
	m_backButton->m_up = m_accelerationButton;
	m_backButton->m_down = m_radButtons.at(0);

	m_backButton->select = std::bind(&UpgradesScreen::backCallback, this);
	m_accelerationButton->select = std::bind(&UpgradesScreen::accelerationCallback, this);
	m_brakingButton->select = std::bind(&UpgradesScreen::brakingCallback, this);
	m_corneringButton->select = std::bind(&UpgradesScreen::corneringCallback, this);

	m_gui.add(m_title);
	m_gui.add(m_accelerationButton);
	m_gui.add(m_brakingButton);
	m_gui.add(m_corneringButton);
	m_gui.add(m_backButton);
	m_gui.add(m_accelerationSlider);
	m_gui.add(m_brakingSlider);
	m_gui.add(m_corneringSlider);

	m_gui.update();

	m_carSprite.setPosition(sf::Vector2f(50, 100));

	setSliders();
}

UpgradesScreen::~UpgradesScreen() {}

void UpgradesScreen::update(XboxController & controller)
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
	else if (m_backButtonPressed)
	{
		transOut(GameState::MainMenu);
	}
	m_gui.processInput(controller);
}

void UpgradesScreen::reset()
{
	m_backButtonPressed = false;
	m_transitionIn = true;
	m_interpolation = 0.f;
}

void UpgradesScreen::render(sf::RenderWindow& window)
{
	window.draw(m_gui);
	window.draw(m_carSprite);
}

void UpgradesScreen::backCallback()
{
	m_backButtonPressed = true;
}

void UpgradesScreen::setSliders()
{
	m_accelerationSlider->setPercentageFull(m_cars.at(m_currentCarIndex).m_acceleration / 300.f);
	m_brakingSlider->setPercentageFull(m_cars.at(m_currentCarIndex).m_deceleration / 300.f);
	m_corneringSlider->setPercentageFull(m_cars.at(m_currentCarIndex).m_turnRate / 300.f);
	m_carSprite.setTexture(g_resourceMgr.textureHolder[m_cars.at(m_currentCarIndex).m_texture], true);
	float width = m_carSprite.getLocalBounds().width;
	float height = m_carSprite.getLocalBounds().height;
	m_carSprite.setScale(sf::Vector2f(300 / width, 150 / height));
}

void UpgradesScreen::radButtonCallback()
{
	for (int i = 0; i < m_radButtons.size(); i++)
	{
		if (m_radButtons.at(i)->getState())
		{
			m_currentCarIndex = i;
			setSliders();
			break;
		}
	}
}

void UpgradesScreen::accelerationCallback()
{
	m_cars.at(m_currentCarIndex).m_acceleration += 25;
}

void UpgradesScreen::brakingCallback()
{
	m_cars.at(m_currentCarIndex).m_deceleration += 25;
}

void UpgradesScreen::corneringCallback()
{
	m_cars.at(m_currentCarIndex).m_turnRate += 25;
}

void UpgradesScreen::setSprite()
{

}