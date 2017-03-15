/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef PAUSE_SCREEN_H
#define PAUSE_SCREEN_H

#include "Screen.h"

/// The pause screen that the player can back into
/// 
/// The pause screen handles all the update and render of the widgets
/// on screen
class PauseScreen : public Screen
{
public:
	PauseScreen();
	~PauseScreen();

	void update(XboxController & controller) override;
	void reset() override;

private:
	void resumeButtonCallback();
	void optionsButtonCallback();
	void quitButtonCallback();

	Label *m_pauseScreenLabel;
	Button *m_resumeButton;
	Button *m_optionsButton;
	Button *m_quitButton;

	bool m_resumeSelected;
	bool m_quitSelected;
	bool m_optionsSelected;
};

#endif