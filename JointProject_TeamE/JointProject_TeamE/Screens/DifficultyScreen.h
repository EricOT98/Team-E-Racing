/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef DIFFICULTY_SCREEN_H
#define DIFFICULTY_SCREEN_H

#include "Screen.h"

/// Displays the widgets the player interacts with in the Difficulty Screen
/// 
/// Initalises all the widgets in the sceen and updates, renders and process
/// the inputs.
class DifficultyScreen : public Screen
{
public:
	DifficultyScreen();
	~DifficultyScreen();

	void update(XboxController & controller) override;
	void reset() override;
	int getNumberOfAI();

private:
	void backButtonCallback();
	void radioButtonSetCallback();

	Label *m_difficultyLabel;
	Label *m_numOfOppLabel;
	std::vector<RadioButton*> m_radioButtons;
	Button *m_backButton;

	bool m_backButtonSelected;
	
};

#endif