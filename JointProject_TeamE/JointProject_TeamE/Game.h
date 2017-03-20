#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include "ResourceManager.h"
#include "LevelLoader.h"
#include "Track.h"
#include "Screens\ScreenManager.h"
#include "Player.h"
#include "AI.h"
#include "Input\KeyboardHandler.h"
#include <iostream>


//GUI
#include "Screens\ConfirmationScreen.h"
#include "Screens\DifficultyScreen.h"
#include "Screens\DisplayOptions.h"
#include "Screens\HelpScreen.h"
#include "Screens\MainMenu.h"
#include "Screens\Options.h"
#include "Screens\PauseScreen.h"
#include "Screens\SoundOptions.h"
#include "Screens\TrophyScreen.h"
#include "Screens\SplashScreen.h"
#include "Screens\UpgradesScreen.h"

#include "Screens\Screen.h"

// For testing
#include "Shader.h"

// Initalize gl3w
#include "GL\gl3w.h"

class Game
{
public:
	Game();
	void run();

protected:
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);
	void resetGame();

	sf::RenderWindow m_window;

	ScreenManager m_screenManager;
	KeyboardHandler *keyboardHandler;
	XboxController m_xboxController;

	//GameState currentGameState = GameState::Play;
	LevelData m_level;

	sf::Texture carTexture;
	Track m_track;
	sf::Sprite carSprite;
	Player m_player;
	std::vector<Racer *> m_racers;
	sf::View raceView;

	// For testing
	Shader m_crtShader;
	 
	// Game Screens
	SplashScreen * m_splashScreen;
	ConfirmationScreen * m_confirmationScreen;
	DifficultyScreen * m_difficultyScreen;
	DisplayOptions * m_displayOptions;
	HelpScreen * m_helpScreen;
	MainMenu * m_mainMenu;
	Options * m_options;
	PauseScreen * m_pauseScreen;
	SoundOptions * m_soundOptions;
	TrophyScreen * m_trophyScreen;
	UpgradesScreen * m_upgradesScreen;

	bool m_reset;
	bool m_transitionInGame;
};

#endif