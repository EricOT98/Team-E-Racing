/// <summary>
/// @author: Eric O' Toole
/// @version: 1.00
/// </summary>

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "Screen.h"
#include "sfeMovie\Movie.hpp"
#include "..\ResourceManager.h"

class SplashScreen : public Screen
{
public:
	SplashScreen();
	~SplashScreen();

	void update(XboxController & controller) override;
	void render(sf::RenderWindow& window) override;
	void reset() override;
protected:
	sfe::Movie m_intro;
	sf::RectangleShape m_foreground;
	sf::Color m_foregroundColor;
	const int MAX_ALPHA = 255;			//Maximum alpha value of the texture

	bool m_fadeIn,m_fadeOut;
	float m_currentAlpha = 0;
	float m_alphaStep = 0;
	float m_fadeTime = 0;
	bool m_playing;
	bool m_skip;
};
#endif //!SPLASHSCREEN
