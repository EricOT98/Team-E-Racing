/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef OPTIONS_H
#define OPTIONS_H

#include "Screen.h"

/// A menu displaying all the options avaible for the player
/// 
/// The Options screen handles all the neccesary widgets on screen
/// and updates the player input and screen navigation.
class Options : public Screen
{
public:
	Options();
	~Options();

	void update(XboxController & controller) override;
	void reset() override;

private:
	void soundButtonCallback();
	void displayButtonCallback();
	void helpButtonCallback();
	void difficultyButtonCallback();
	void backButtonCallback();

	Label *m_titleLabel;
	Button *m_soundButton;
	Button *m_displayButton;
	Button *m_helpButton;
	Button *m_difficultyButton;
	Button *m_backButton;

	bool m_soundButtonSelected;
	bool m_displayButtonSelected;
	bool m_helpButtonSelected;
	bool m_difficultyButtonSelected;
	bool m_backButtonSelected;
};

#endif // !OPTIONS_H