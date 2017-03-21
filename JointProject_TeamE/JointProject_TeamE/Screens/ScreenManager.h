/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef  SCRENMANAGER_H
#define SCREENMANAGER_H

#include "Screen.h"

/// <summary>
/// Brief: Class used to manage all of the screens
/// 
/// Detail: Class used to update and render each 
/// screen within the game based on the current GameState
/// </summary>
class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();
	void update(XboxController &controller);
	void render(sf::RenderWindow& window);
	void add(Screen *Screen);
	void setActive(GameState gameStateIn);
	bool getState();
	GameState getGameState();
private:
	std::vector<Screen *> screens; // Screen container
	GameState m_gameState; // Current game state
	GameState m_nextGameState;
	int m_currentScreen; // Current active screen
	sf::Sprite m_backgroundSprite; // Background sprite to be drawn
	bool m_active;
};

#endif
