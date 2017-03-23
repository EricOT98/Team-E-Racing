#ifndef HUDSYSTEM_H
#define HUDSYSTEM_H

#include <SFML\Graphics.hpp>
#include "ResourceManager.h"
#include "MathUtility.h"
#include "Racer.h"

class HudSystem
{
public:
	HudSystem();

	void update(Racer & player);
	void render(sf::RenderWindow & window);
	void reset();
	void pauseTimer();
	void resumeTimer();
	void startRecordingTime();
	bool getRecording();
private:
	sf::Texture m_hudTexture;
	sf::Sprite m_hudSprite;
	sf::Clock m_clock;
	sf::Time m_time;
	sf::Color m_translucent;

	sf::Text m_lapText;
	sf::Text m_lapTimeText;
	float m_lapTime;
	bool m_raceStarted;
	bool m_paused;

	float m_interpolation;
	float m_timeCounter;
	int m_currentLap;
};
#endif;
