/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef TROPHY_SCREEN_H
#define TROPHY_SCREEN_H

#include "..\ResourceManager.h"
#include "..\Input\XboxController.h"
#include "Screen.h"
#include "..\GUI\Gui.h"
#include "..\GUI\Button.h"

class TrophyScreen : Screen
{
public:
	TrophyScreen();
	~TrophyScreen();

	void update();
	void render(sf::RenderWindow &window);
	void processInput(XboxController &controller);

private:
	void checkScreenTransition(Button *button, GameScreenState stateToChangeTo);

	Gui m_trophyScreenGUI;
	Label *m_titleLabel;
	Button *m_backButton;

	sf::Texture *m_trophiesTexture;
};

#endif