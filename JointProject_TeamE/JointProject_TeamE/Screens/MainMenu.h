///// <summary>
///// @author Darren Sweeney
///// @version 1.0
///// </summary>
//
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Screen.h"

/// The Main Menu screen that the player navigates in to other screens.
/// 
/// The Main Menu contains button objects that will be updated in the Gui screen
/// manager and allows the player to navigate the men
class MainMenu : public Screen
{
public:
	MainMenu(bool & gameReset);
	~MainMenu();

	void update(XboxController& controller) override;
	void render(sf::RenderWindow &window) override;
	void reset() override;

private:
	
	void playButtonCallback();
	void upgradesButtonCallback();
	void trophiesButtonCallback();
	void optionsButtonCallback();
	void creditsButtonCallback();
	void exitButtonCallback();

	Label *m_title;
	Button *m_playButton;
	Button *m_upgradesButton;
	Button *m_trophiesButton;
	Button *m_optionsButton;
	Button *m_creditsButton;
	Button *m_exitButton;

	bool m_playButtonSelected;
	bool m_upgradesButtonSelected;
	bool m_trophiesButtonSelected;
	bool m_optionsButtonSelected;
	bool m_creditsButtonSelected;
	bool m_exitButtonSelected;

	bool & m_gameReset;
};

#endif 