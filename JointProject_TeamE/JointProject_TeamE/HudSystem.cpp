#include "HudSystem.h"

/// <summary>
/// Default constructor of the in game hud to display
/// all relevant information to the player
/// </summary>
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

	m_timeCounter = 0;
	m_currentLap = 0;
	m_lapTime = 0;   
	m_fastestLapTime = 0;
	m_lapText.setString("Lap: " + std::to_string(m_currentLap + 1) + "/3");
	m_lapTimeText.setString("Lap Time: ");
	m_fastestLapText.setString("Fastest Lap Time: ");
}

/// <summary>
/// If not transitioned in transition the hud into position
/// else record the players times
/// </summary>
/// <param name="player"></param>
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
		if(newLap!= 3)
		m_lapText.setString("Lap: " + std::to_string(m_currentLap + 1) + "/3");

		recordLapTime();
		std::stringstream stream;
		stream << std::setprecision(4) << m_fastestLapTime;

		m_fastestLapText.setString("Fastest Lap Time: " + stream.str());
	}
	m_lapTimeText.setString("Lap Time: " + std::to_string(static_cast<int>(m_lapTime)));
}

/// <summary>
/// Render the hud to the screen
/// </summary>
/// <param name="window">The current render window</param>
void HudSystem::render(sf::RenderWindow & window)
{
	//window.draw(m_hudSprite);
	window.draw(m_lapText);
	window.draw(m_lapTimeText);
	window.draw(m_fastestLapText);
}

/// <summary>
/// Reset the hud to be used again
/// </summary>
void HudSystem::reset()
{
	m_clock.restart();
	m_interpolation = 0;
	m_raceStarted = false;
	m_paused = false;
}

/// <summary>
/// Pause the huds time recording
/// </summary>
void HudSystem::pauseTimer()
{
	m_paused = true;
}

/// <summary>
/// Resume the huds timer
/// </summary>
void HudSystem::resumeTimer()
{
	m_paused = false;
}

/// <summary>
/// Start recording the huds time
/// </summary>
void HudSystem::startRecordingTime()
{
	m_clock.restart();
	m_lapTime = 0;
	m_raceStarted = true;
	m_paused = false;
}

/// <summary>
/// Get if the hud is currently recording players time
/// </summary>
/// <returns>Bool for recording started</returns>
bool HudSystem::getRecording()
{
	return m_raceStarted;
}

/// <summary>
/// Boolean for checking if the race has finished
/// </summary>
/// <returns></returns>
bool HudSystem::raceFinished()
{
	if (m_currentLap == 3) 
	return true;
	else
	return false;
}

/// <summary>
/// Records the fastest lap time
/// </summary>
void HudSystem::recordLapTime()
{
	if (m_fastestLapTime == 0)
		m_fastestLapTime = m_lapTime;
	else if (m_lapTime < m_fastestLapTime)
		m_fastestLapTime = m_lapTime;
	m_clock.restart();
}
