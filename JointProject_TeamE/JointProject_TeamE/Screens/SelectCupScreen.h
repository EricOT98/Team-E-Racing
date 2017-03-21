#ifndef SELECTCUPSCREEN_H
#define SELECTCUPSCREEN_H

#include "Screen.h"
#include "..\Player.h"
#include "..\LevelLoader.h"

class SelectCupScreen : public Screen
{
public:
	SelectCupScreen(std::vector<CarData> & carsIn, std::vector<CupData> & cupsIn, std::vector<Racer *> & racers, int screenWidth);
	~SelectCupScreen();
	void update(XboxController & controller) override;
	void reset() override;
private:
	void confirmButtonCallback();
	void backButtonCallback();

	Label * m_title;
	Button * m_backButton;
	Button * m_confirmButton;
	std::vector<RadioButton *> m_radButtons;

	Player * m_player;
	std::vector<CarData> & m_cars;
	std::vector<CupData> & m_cups;
	std::vector<Racer *> & m_racers;

	bool m_backButtonPressed;
	bool m_confirmButtonPressed;
	int m_currentCarIndex;
};

#endif
