///// <summary>
///// @author Darren Sweeney
///// @version 1.0
///// </summary>
//
//#ifndef DIFFICULTY_SCREEN_H
//#define DIFFICULTY_SCREEN_H
//
//#include "Screen.h"
//#include "..\Input\XboxController.h"
//#include "..\GUI\Gui.h"
//#include "..\GUI\RadioButton.h"
//#include "..\GUI\Button.h"
//
///// Displays the widgets the player interacts with in the Difficulty Screen
///// 
///// Initalises all the widgets in the sceen and updates, renders and process
///// the inputs.
//class DifficultyScreen : Screen
//{
//public:
//	DifficultyScreen();
//	~DifficultyScreen();
//
//	void update();
//	void render(sf::RenderWindow &window);
//	void processInput(XboxController &controller);
//
//private:
//	void checkScreenTransition(Button *button, GameScreenState stateToChangeTo);
//
//	Gui m_difficultyScreenGUI;
//	Label *m_difficultyLabel;
//	Label *m_numOfOppLabel;
//	std::vector<RadioButton*> m_radioButtons;
//	Button *m_backButton;
//	
//};
//
//#endif