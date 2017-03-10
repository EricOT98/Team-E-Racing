/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef SCREEN_H
#define SCREEN_H

#include <SFML\Graphics.hpp>

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

protected:
	virtual void update();
	virtual void render();
	virtual void processInput(sf::Event &event);
};

#endif // !SCREEN_H