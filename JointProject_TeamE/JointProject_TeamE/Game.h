#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include "ResourceManager.h"
#include "LevelLoader.h"
#include "Track.h"
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

	enum class GameState
	{
		Play
	};

	GameState currentGameState = GameState::Play;
	LevelData m_level;

	sf::Texture carTexture;
	Track m_track;
	sf::Sprite carSprite;
};

#endif
