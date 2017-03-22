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

	sf::Texture m_trophiesTexture;
	sf::Sprite m_trophiesSprite;
	sf::Vector2f m_position;
	bool m_trophyUnlocked[3];

	bool m_backButtonSelected;
};

#endif