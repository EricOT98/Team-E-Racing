#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "MainMenu.h"
#include "Options.h"
#include "SoundOptions.h"
#include "DifficultyScreen.h"
#include "HelpScreen.h"
#include "PauseScreen.h"
#include "ConfirmationScreen.h"
#include "DisplayOptions.h"

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();

	void init();
	void update();
	void render(sf::RenderWindow &window);
	void processInput(XboxController &controller);

private:
	MainMenu *m_mainMenu;
	Options *m_optionsMenu;
	SoundOptions *m_soundOptions;
	DifficultyScreen *m_difficultyScreen;
	HelpScreen *m_helpScreen;
	DisplayOptions *m_displayOpitions;
	PauseScreen *m_pauseScreen;
	ConfirmationScreen *m_confirmationScreen;
};

#endif