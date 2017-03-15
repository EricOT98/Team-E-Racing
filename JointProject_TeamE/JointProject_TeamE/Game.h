#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include "ResourceManager.h"
#include "LevelLoader.h"
#include "Track.h"
#include "Screens\ScreenManager.h"
#include "Player.h"
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
//GUI



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

	sf::RenderWindow m_window;

	ScreenManager m_screenManager;
	KeyboardHandler *keyboardHandler;
	XboxController m_xboxController;

	enum class GameState
	{
		Menu,
		Play
	};

	GameState currentGameState = GameState::Menu;
	LevelData m_level;

	sf::Texture carTexture;
	Track m_track;
	sf::Sprite carSprite;
	Player m_player;
	std::vector<Racer *> m_racers;
	sf::View raceView;

	// Game Screens
	ConfirmationScreen * m_confirmationScreen;
	DifficultyScreen * m_difficultyScreen;
	DisplayOptions * m_displayOptions;
	HelpScreen * m_helpScreen;
	MainMenu * m_mainMenu;
	Options * m_options;
	//PauseScreen * m_pauseScreen;
	//SoundOptions * m_soundOptions;
	//TrophyScreen * m_trophyScreen;

	// Game Screens
};

#endif
