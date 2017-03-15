/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef SCREEN_H
#define SCREEN_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "..\Input\KeyboardHandler.h"
#include "..\Input\XboxController.h"
#include "..\GUI\Gui.h"
#include "..\GUI\Slider.h"
#include "..\GUI\Button.h"
#include "..\GUI\RadioButton.h"
#include "..\GUI\CheckBox.h"

/// <summary>
/// Define the gamestate here as it is accessible to everything that neds it at this point
/// as all screens have a GameSate and the ScreenManager has a GameState
/// </summary>
enum class GameState
{
	SplashScreen,
	MainMenu,
	OptionsScreen,
	QuitScreen,
	GamePlay,
	EndGameState,
	DifficultyScreen,
	DisplayOptionsScreen,
	HelpScreen,
	PauseScreen,
	SoundOptions,
	UpgradesScreen,
	TrophyScreen,
	CreditsScreen
};

/// <summary>
/// Brief: General screen class inherited by all objects of type screen
///
/// Detail: Handles general functionality of the in game screens like drawing etc
/// </summary>
class Screen
{
public:
	Screen(GameState gameStateIn);
	virtual void update(XboxController& controller) = 0; // pure virtual update (needs to be overrided)
	virtual void render(sf::RenderWindow& window);
	GameState getGameState();
	GameState getNextGameState();
	void resetNextGameState();
	void setColors();
	virtual void reset() = 0; // pure virtual reset (needs to be overrided)
protected:
	void transOut(GameState gameStateIn);

	// GameState variables
	GameState m_gameState;
	GameState m_nextGameState;

	// GUI object
	Gui m_gui;

	float m_interpolation;
	bool m_transitionIn;
};

#endif
