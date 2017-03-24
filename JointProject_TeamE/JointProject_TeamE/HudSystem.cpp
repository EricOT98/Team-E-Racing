#include "HudSystem.h"

HudSystem::HudSystem()
{
	m_interpolation = 0;
	m_raceStarted = false;
	m_translucent = sf::Color(0, 0, 0, 0);
	m_lapText.setPosition(sf::Vector2f(900.0f, 400.0f));
	m_lapTimeText.setPosition(sf::Vector2f(900.0f, 400.0f));
	m_fastestLapText.setPosition(sf::Vector2f(900.0f, 400.0f));

	m_lapText.setFont(g_resourceMgr.fontHolder["GameFont"]);
	m_lapTimeText.setFont(g_resourceMgr.fontHolder["GameFont"]);
	m_fastestLapText.setFont(g_resourceMgr.fontHolder["GameFont"]);

	m_lapText.setColor(sf::Color::Magenta);
	m_lapTimeText.setColor(sf::Color::Magenta);
	m_fastestLapText.setColor(sf::Color::Magenta);

	m_lapText.setString("Lap: ");
	m_lapTimeText.setString("Lap Time: ");
	m_fastestLapText.setString("Fastest Lap Time: ");
	m_timeCounter = 0;
	m_currentLap = 0;
	m_lapTime = 0;   
	m_fastestLapTime = 0;
}

void HudSystem::update(Racer & player)
{
	m_time = m_clock.getElapsedTime();
	m_timeCounter += m_time.asSeconds() / 1000.0f;
	if (m_interpolation <= 1.0f)
	{
		m_interpolation += m_timeCounter / 10.0f;
		sf::Vector2f m_lapTextPosition = m_lapText.getPosition();
		sf::Vector2f m_lapTimePosition = m_lapTimeText.getPosition();
		sf::Vector2f m_fastestLapPosition = m_fastestLapText.getPosition();
		m_lapText.setPosition(lerp(m_lapTextPosition, sf::Vector2f(10.0f, 10.0f), m_interpolation));
		m_lapTimeText.setPosition(lerp(m_lapTimePosition, sf::Vector2f(10.0f, 45.0f), m_interpolation));
		m_fastestLapText.setPosition(lerp(m_fastestLapPosition, sf::Vector2f(10.0f, 75.0f), m_interpolation));
	}
	else
	{
		if (!m_paused && m_raceStarted)
		{
			m_lapTime = m_clock.getElapsedTime().asSeconds();
		}
	}
	int newLap = player.getLap();
	if (m_currentLap != newLap) {
		m_currentLap = newLap;
		m_lapText.setString("Lap: " + std::to_string(m_currentLap));
		recordLapTime();
		std::stringstream stream;
		stream << std::setprecision(4) << m_fastestLapTime;

		m_fastestLapText.setString("Fastest Lap Time: " + stream.str());
	}
	m_lapTimeText.setString("Lap Time: " + std::to_string(static_cast<int>(m_lapTime)));
}

void HudSystem::render(sf::RenderWindow & window)
{
	//window.draw(m_hudSprite);
	window.draw(m_lapText);
	window.draw(m_lapTimeText);
	window.draw(m_fastestLapText);
}

void HudSystem::reset()
{
	m_clock.restart();
	m_interpolation = 0;
	m_raceStarted = false;
	m_paused = false;
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
	m_lapTime = 0;
	m_raceStarted = true;
	m_paused = false;
}

bool HudSystem::getRecording()
{
	return m_raceStarted;
}

bool HudSystem::raceFinished()
{
	if (m_currentLap == 0) 
	return true;
	else
	return false;
}

void HudSystem::recordLapTime()
{
	if (m_fastestLapTime == 0)
		m_fastestLapTime = m_lapTime;
	else if (m_lapTime < m_fastestLapTime)
		m_fastestLapTime = m_lapTime;
	m_clock.restart();
}
