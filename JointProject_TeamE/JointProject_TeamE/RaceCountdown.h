/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef RACE_COUNT_DOWN_H
#define RACE_COUNT_DOWN_H

#include <SFML\Graphics.hpp>
#include "ResourceManager.h"
#include "MathUtility.h"

/// Shows player time till the race starts
/// 
/// Shows player time till the race starts by displaying
/// a 3, 2, 1, Go Sprite to screen.
class RaceCountdown
{
public:
	RaceCountdown();

	void update();
	void render(sf::RenderWindow &window);
	void reset();
	bool getFinishedCountingDown();

private:
	sf::Texture m_countdownTexture;
	sf::Sprite m_countdownSprite;
	sf::IntRect m_countdownRec[4];
	sf::Vector2f m_position;

	sf::Clock m_clock;
	sf::Time m_time;
	double m_timeCounter;
	float m_interpolation;
	float m_alpha;
	unsigned int m_recIndex;
	bool m_finishedCountingDown;
};

#endif