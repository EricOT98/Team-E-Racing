#ifndef UPGRADESSCREEN_H
#define UPGRADESSCREEN_H

#include "Screen.h"
#include "../LevelLoader.h"
#include "../ResourceManager.h"

class UpgradesScreen : public Screen
{
public:
	UpgradesScreen(std::vector<CarData> & carsIn, int screenWidth);
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

	// Sprite to be displayed
	sf::Sprite m_carSprite;

	bool m_backButtonPressed;
	std::vector<CarData> & m_cars;
	int m_currentCarIndex;
};

#endif // !UPGRADESSCREEN_H

