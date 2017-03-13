/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef OPTIONS_H
#define OPTIONS_H

#include "Screen.h"
#include "..\Input\XboxController.h"
#include "..\GUI\Button.h"
#include "..\GUI\Gui.h"

/// A menu displaying all the options avaible for the player
/// 
/// The Options screen handles all the neccesary widgets on screen
/// and updates the player input and screen navigation.
class Options : public Screen
{
public:
	Options();
	~Options();

	void update();
	void render(sf::RenderWindow &window);
	void processInput(XboxController &controller);

private:
	void checkScreenTransition(Button *button, GameScreenState stateToChangeTo);

	Gui m_optionsGUI;
	Label *m_titleLabel;
	Button *m_soundButton;
	Button *m_displayButton;
	Button *m_helpButton;
	Button *m_difficultyButton;
	Button *m_backButton;
};

#endif // !OPTIONS_H