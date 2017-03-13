/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef HELP_SCREEN_H
#define HELP_SCREEN_H

#include "Screen.h"
#include "..\Input\XboxController.h"
#include "..\Gui\Gui.h"
#include "..\GUI\Button.h"

/// The help screen containing all the help information
/// 
/// The help screen contatins all the help text and the back button
/// in the widgets that are updated and rendered
class HelpScreen : Screen
{
public:
	HelpScreen();
	~HelpScreen();

	void update();
	void render(sf::RenderWindow &window);
	void processInput(XboxController &controller);

private:
	void checkScreenTransition(Button *button, GameScreenState stateToChangeTo);

	Gui m_helpScreenGUI;
	std::vector<Label*> m_helpScreenText;
	Button *m_backButton;
};

#endif