/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef TROPHY_SCREEN_H
#define TROPHY_SCREEN_H

#include "Screen.h"

class TrophyScreen : public Screen
{
public:
	TrophyScreen();
	~TrophyScreen();

	void update(XboxController & controller) override;
	void render(sf::RenderWindow &window) override;
	void reset() override;

private:
	void backButtonCallback();

	Label *m_titleLabel;
	Button *m_backButton;

	bool m_backButtonSelected;

	sf::Sprite m_trophySprite1;
	sf::Sprite m_trophySprite2;
	sf::Sprite m_trophySprite3;
};

#endif