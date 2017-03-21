/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef CREDITS_H
#define CREDITS_H

#include "Screen.h"
#include "sfeMovie\Movie.hpp"
#include "..\ResourceManager.h"

class CreditsScreen : public Screen
{
public:
	CreditsScreen();
	~CreditsScreen();

	void update(XboxController & controller) override;
	void render(sf::RenderWindow& window) override;
	void reset() override;

protected:
	sfe::Movie m_creditsVideo;
	bool m_playing;
	bool m_skip;
	bool m_startVideo;
};

#endif