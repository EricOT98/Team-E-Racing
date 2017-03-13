/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef DISPLAY_OPTIONS_H
#define DISPLAY_OPTIONS_H

#include "Screen.h"
#include "..\Input\XboxController.h"
#include "..\GUI\Button.h"
#include "..\GUI\Slider.h"
#include "..\GUI\CheckBox.h"
#include "..\GUI\Gui.h"

/// A menu displaying all the options assocaite with display
/// 
/// The Display Options screen handles all the neccesary widgets on screen
/// and updates the player input and screen navigation
class DisplayOptions : Screen
{
public:
	DisplayOptions();
	~DisplayOptions();

	void update();
	void render(sf::RenderWindow &window);
	void processInput(XboxController &controller);

private:
	void checkScreenTransition(Button *button, GameScreenState stateToChangeTo);

	Gui m_displayOpitionsGUI;
	Label *m_titleLabel;
	Button *m_backButton;
};

#endif