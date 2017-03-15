/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef HELP_SCREEN_H
#define HELP_SCREEN_H

#include "Screen.h"

/// The help screen containing all the help information
/// 
/// The help screen contatins all the help text and the back button
/// in the widgets that are updated and rendered
class HelpScreen : public Screen
{
public:
	HelpScreen();
	~HelpScreen();

	void update(XboxController & controller) override;
	void reset() override;

private:
	void backButtonCallback();

	std::vector<Label*> m_helpScreenText;
	Button *m_backButton;

	bool m_backButtonSelected;
};

#endif