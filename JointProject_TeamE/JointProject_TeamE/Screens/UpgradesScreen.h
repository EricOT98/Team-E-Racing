#ifndef UPGRADESSCREEN_H
#define UPGRADESSCREEN_H

#include "Screen.h"
#include "../LevelLoader.h"
#include "../ResourceManager.h"

class UpgradesScreen : public Screen
{
public:
	UpgradesScreen(std::vector<CarData> & carsIn,int & credits, int screenWidth);
	~UpgradesScreen();

	void update(XboxController & controller) override;
	void reset() override;
	void render(sf::RenderWindow& window) override;
private:
	void backCallback();
	void accelerationCallback();
	void brakingCallback();
	void corneringCallback();
	void radButtonCallback();
	void setSliders();
	void setSprite();
	void checkAvailable(bool & upgradeAvailable);
	void purchaseUpgrade(float & upgrade);
	void setDisplayInfo(bool & upgradeAvailable);

	// GUI elements
	Label * m_title;
	std::vector<RadioButton *> m_radButtons;
	Button * m_accelerationButton;
	Button * m_brakingButton;
	Button * m_corneringButton;
	Button * m_backButton;
	Slider * m_accelerationSlider;
	Slider * m_brakingSlider;
	Slider * m_corneringSlider;
	sf::Text m_costText;
	sf::Text m_creditsText;

	// Sprite to be displayed
	sf::Sprite m_carSprite;

	bool m_backButtonPressed;
	std::vector<CarData> & m_cars;
	int m_currentCarIndex;
	int & m_credits;
	bool m_accelerationUpgradeAvailable;
	bool m_brakingUpgradeAvailable;;
	bool m_corneringUpgradeAvailable;
	int m_upgradeCost;
	int m_baseCost;
	sf::Vector2f m_costPosition;
	sf::Vector2f m_creditsPosition;
};

#endif // !UPGRADESSCREEN_H

