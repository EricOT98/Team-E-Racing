/// <summary>
/// @author: Eric O' Toole
/// @version: 1.0
/// </summary>
#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "Screen.h"

/// <summary>
/// A Menu displaying all the game over options available to the user
/// 
///  The GameOver screen handles all the neccesary widgets on screen
///  and updates the player input and screen navigation.
/// </summary>
class GameOverScreen : public Screen
{
public:
	GameOverScreen();
	~GameOverScreen();

	void update(XboxController & controller) override;
	void reset() override;

private:
	void backToMenuCallback();
	void quitGameCallback();

	Label *m_titleLabel;
	Label *m_fastestLapTimeLabel;
	Button *m_quitButton;
	Button* m_backButton;

	bool m_quitButtonSelected;
	bool m_backButtonSelected;
};
#endif;
