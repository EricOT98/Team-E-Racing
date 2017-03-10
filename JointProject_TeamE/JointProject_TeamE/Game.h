#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include "ResourceManager.h"
#include "LevelLoader.h"
#include "Track.h"
#include "Screens\ScreenManager.h"
#include "Player.h"
#include <iostream>

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
	XboxController m_xboxController;

	enum class GameState
	{
		MainMenu,
		Play
	};

	GameState currentGameState = GameState::MainMenu;
	LevelData m_level;

	Track m_track;
	Player m_player;
};

#endif
