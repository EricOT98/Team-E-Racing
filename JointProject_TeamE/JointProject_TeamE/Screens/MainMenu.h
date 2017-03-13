/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Screen.h"
#include "..\GUI\Gui.h"
#include "..\GUI\Button.h"
#include "..\Input\XboxController.h"

/// The Main Menu screen that the player navigates in to other screens.
/// 
/// The Main Menu contains button objects that will be updated in the Gui screen
/// manager and allows the player to navigate the men
class MainMenu : Screen
{
public:
	MainMenu();
	~MainMenu();

	void update();
	void render(sf::RenderWindow &window);  
	void processInput(XboxController &controller);

private:
	void checkScreenTransition(Button *button, GameScreenState stateToChangeTo);

	Gui m_screenGUI;
	Button *m_raceButton;
	Button *m_upgradesButton;
	Button *m_trophiesButton;
	Button *m_optionsButton;
	Button *m_creditsButton;
	Button *m_exitButton;
};

#endif 