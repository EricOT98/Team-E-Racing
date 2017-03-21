#ifndef SELECTCARSCREEN_H
#define SELECTCARSCREEN_H

#include "Screen.h"
#include "..\Player.h"
#include "..\LevelLoader.h"

class SelectCarScreen : public Screen
{
public:
	SelectCarScreen(std::vector<CarData> & carsIn, Player * playerIn, int screenWidth);
	~SelectCarScreen();
	void update(XboxController & controller) override;
	void reset() override;
private:
	void confirmButtonCallback();
	void backButtonCallback();
	void radButtonCallback();
	void setSliders();

	Label * m_title;
	Button * m_backButton;
	Button * m_confirmButton;
	std::vector<RadioButton *> m_radButtons;
	Slider * m_accelerationSlider;
	Slider * m_brakingSlider;
	Slider * m_corneringSlider;

	Player * m_player;
	std::vector<CarData> & m_cars;

	bool m_backButtonPressed;
	bool m_confirmButtonPressed;
	bool m_resetSliders;
	int m_currentCarIndex;
};

#endif
