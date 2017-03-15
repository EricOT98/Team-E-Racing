/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef DISPLAY_OPTIONS_H
#define DISPLAY_OPTIONS_H

#include "Screen.h"

/// A menu displaying all the options assocaite with display
/// 
/// The Display Options screen handles all the neccesary widgets on screen
/// and updates the player input and screen navigation
class DisplayOptions : public Screen
{
public:
	DisplayOptions();
	~DisplayOptions();

	void update(XboxController & controller) override;
	void reset() override;

private:
	void backButtonCallback();

	Label *m_titleLabel;
	Button *m_backButton;

	bool m_backButtonSelected;
};

#endif