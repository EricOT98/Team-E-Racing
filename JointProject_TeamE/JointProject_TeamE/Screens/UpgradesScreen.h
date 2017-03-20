#ifndef UPGRADESSCREEN_H
#define UPGRADESSCREEN_H

#include "Screen.h"

class UpgradesScreen : public Screen
{
public:
	UpgradesScreen();
	~UpgradesScreen();

	void update(XboxController & controller) override;
	void reset() override;
	void render(sf::RenderWindow& window) override;
private:
	void backCallback();
	Label * m_title;
	std::vector<RadioButton *> m_radButtons;
	Button * m_accelerationButton;
	Button * m_brakingButton;
	Button * m_corneringButton;
	Button * m_backButton;

	sf::Sprite m_carSprite;

	bool m_backButtonPressed;

};

#endif // !UPGRADESSCREEN_H

