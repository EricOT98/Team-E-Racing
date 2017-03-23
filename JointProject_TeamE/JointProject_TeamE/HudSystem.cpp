#include "HudSystem.h"

HudSystem::HudSystem()
{
	m_interpolation = 0;
	m_raceStarted = false;
	m_translucent = sf::Color(0, 0, 0, 0);
	m_lapText.setPosition(sf::Vector2f(900.0f, 400.0f));
	m_lapTimeText.setPosition(sf::Vector2f(900.0f, 400.0f));
	m_lapText.setFont(g_resourceMgr.fontHolder["GameFont"]);
	m_lapTimeText.setFont(g_resourceMgr.fontHolder["GameFont"]);
	m_lapText.setColor(sf::Color::Magenta);
	m_lapTimeText.setColor(sf::Color::Magenta);
	m_lapText.setString("Lap: ");
	m_lapTimeText.setString("Lap Time: ");
	m_timeCounter = 0;
	m_currentLap = 0;
	m_lapTime = 0;                   
}

void HudSystem::update(Racer & player)
{
	m_time = m_clock.getElapsedTime();
	m_timeCounter += m_time.asSeconds() / 1000.0f;
	if (m_interpolation <= 1.0f)
	{
		m_interpolation += m_timeCounter / 100.0f;
	}
	else
	{
		if (!m_paused && m_raceStarted)
		{
			m_lapTime = m_clock.getElapsedTime().asSeconds();
		}
	}
	sf::Vector2f m_lapTextPosition = m_lapText.getPosition();
	sf::Vector2f m_lapTimePosition = m_lapTimeText.getPosition();
	m_lapText.setPosition(lerp(m_lapTextPosition, sf::Vector2f(10.0f, 10.0f), m_interpolation));
	m_lapTimeText.setPosition(lerp(m_lapTimePosition, sf::Vector2f(10.0f, 45.0f), m_interpolation));
	int newLap = player.getLap();
	if (m_currentLap != newLap) {
		m_currentLap = newLap;
		m_lapText.setString("Lap: " + std::to_string(m_currentLap));
	}
	m_lapTimeText.setString("Lap Time: " + std::to_string(static_cast<int>(m_lapTime)));
}

void HudSystem::render(sf::RenderWindow & window)
{
	//window.draw(m_hudSprite);
	window.draw(m_lapText);
	window.draw(m_lapTimeText);
}

void HudSystem::reset()
{
	m_interpolation = 0;
}

void HudSystem::pauseTimer()
{
	m_paused = true;
}

void HudSystem::resumeTimer()
{
	m_paused = false;
}

void HudSystem::startRecordingTime()
{
	m_clock.restart();
	m_raceStarted = true;
	m_paused = false;
}

bool HudSystem::getRecording()
{
	return m_raceStarted;
}
