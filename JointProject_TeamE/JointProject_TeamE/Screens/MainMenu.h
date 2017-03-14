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
	MainMenu();
	~MainMenu();

	void update(XboxController& controller) override;
	void render(sf::RenderWindow &window) override;
	void reset() override;

private:
	void playButtonSelected();
	void upgradesButtonSelected();
	void trophiesButtonSelected();
	void optionsButtonSelected();
	void creditsButtonSelected();
	void exitButtonSelected();

	Label *m_title;
	Button *m_playButton;
	Button *m_upgradesButton;
	Button *m_trophiesButton;
	Button *m_optionsButton;
	Button *m_creditsButton;
	Button *m_exitButton;
};

#endif 