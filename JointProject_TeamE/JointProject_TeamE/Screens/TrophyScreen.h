/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef TROPHY_SCREEN_H
#define TROPHY_SCREEN_H

#include "Screen.h"

/// Displays the trophys on screen
/// 
/// Displays the trophys on screen, updates and renders the trophy screen.
/// Provides a method to set unlocked trophies.
class TrophyScreen : public Screen
{
public:
	TrophyScreen();
	~TrophyScreen();

	void update(XboxController & controller) override;
	void render(sf::RenderWindow &window) override;
	void reset() override;
	void unlockTrophy(int trophyIndex);

private:
	void backButtonCallback();

	Label *m_titleLabel;
	Button *m_backButton;
	Label *m_trophyTitle[3];
	std::string m_trophyNames[3];

	sf::Texture m_trophyTexture;
	sf::Sprite m_trophySprite[3];
	sf::Vector2f m_trophyPosition[3];
	bool m_trophyUnlocked[3];

	bool m_backButtonSelected;
};

#endif