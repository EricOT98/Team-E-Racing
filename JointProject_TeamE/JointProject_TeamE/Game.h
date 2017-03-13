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

	GameState currentGameState = GameState::Play;
	LevelData m_level;

	sf::Texture carTexture;
	Track m_track;
	sf::Sprite carSprite;
	Player m_player;
	std::vector<Racer *> m_racers;
	sf::View raceView;
};

#endif
