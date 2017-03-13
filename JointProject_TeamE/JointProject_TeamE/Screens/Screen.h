/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef SCREEN_H
#define SCREEN_H

#include <SFML\Graphics.hpp>

enum class GameScreenState
{
	MainMenuScreen,
	OptionsScreen,
	SoundOptionsScreen,
	DifficultyScreen,
	QuitConfirmation,
	QuitGame
};

/// Base class Screen for other game screen in the game
/// 
/// The base class Screen provides an interfaces for other
/// game screens in the game.
class Screen
{
public:
	Screen();
	virtual ~Screen();

	bool m_active;

	static GameScreenState currentGameState;

protected:
	virtual void update();
	virtual void render();
	virtual void processInput(sf::Event &event);

	bool m_transitionIn;
	bool m_transitionOut;
	float m_interpolation;
};

#endif // !SCREEN_H