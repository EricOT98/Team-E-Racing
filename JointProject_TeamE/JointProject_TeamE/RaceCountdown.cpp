#include "RaceCountdown.h"

/// <summary>
/// Initalise the texture rectangles for get the texture atlas from the resource manager
/// </summary>
RaceCountdown::RaceCountdown()
{
	// Get the texture atlas from the resource manager
	m_countdownTexture = g_resourceMgr.textureHolder["Countdown"];
	
	// Initalise the rectangles for the different textures on the texture atlas
	m_countdownRec[0] = sf::IntRect(0, 0, 120, 200);	// 3
	m_countdownRec[1] = sf::IntRect(175, 0, 120, 200);	// 2
	m_countdownRec[2] = sf::IntRect(375, 0, 120, 200);	// 1
	m_countdownRec[3] = sf::IntRect(545, 0, 300, 200);	// GO!

	reset();
	m_countdownSprite.setTexture(m_countdownTexture);
	m_countdownSprite.setTextureRect(m_countdownRec[0]);
	// Set the position off screen
	m_position = sf::Vector2f(900.0f, 400.0f);
	m_countdownSprite.setPosition(m_position);
	m_countdownSprite.setOrigin(m_countdownRec[0].width / 2, m_countdownRec[0].height / 2);
	m_finishedCountingDown = false;
}

/// <summary>
/// Update the transitions of the 3, 2, 1 count down. 
/// When a texture is faded out a new texture rectangle is assigned 
/// and the transitions values reset.
/// </summary>
void RaceCountdown::update()
{
	m_time = m_clock.getElapsedTime();
	m_timeCounter += m_time.asSeconds() / 1000.0;

	if (m_interpolation <= 1.0f)
	{
		m_interpolation += m_timeCounter / 20.0f;
	}
	else
	{
		m_alpha -= 50.0f;

		if (m_alpha <= 1.0f && m_recIndex <= 3)
		{
			m_interpolation = 0.0f;
			// Increase the current rectangle index
			m_recIndex++;
			m_countdownSprite.setTextureRect(m_countdownRec[m_recIndex]);
			// Sets the origin of the new texture
			m_countdownSprite.setOrigin(m_countdownRec[m_recIndex].width / 2, m_countdownRec[m_recIndex].height / 2);
			m_timeCounter = 0.0f;
			m_position = sf::Vector2f(900.0f, 400.0f);
			m_alpha = 255.0f;
		}
	}

	if (m_recIndex == 3 && m_interpolation >= 0.6f)
	{
		m_finishedCountingDown = true;
	}

	// Animated the position of the current texture to the center of the screen.
	m_position = lerp(m_position, sf::Vector2f(400.0f, 100.0f), m_interpolation);
	m_countdownSprite.setPosition(m_position);
	m_countdownSprite.setColor(sf::Color(255, 255, 255, m_alpha));
}

/// <summary>
/// Renders the count down timer
/// </summary>
/// <param name="window">A reference to a render window</param>
void RaceCountdown::render(sf::RenderWindow &window)
{
	window.draw(m_countdownSprite);
}

/// <summary>
/// Resets the count down timer
/// </summary>
void RaceCountdown::reset()
{
	m_countdownSprite.setTexture(m_countdownTexture);
	m_countdownSprite.setTextureRect(m_countdownRec[0]);
	// Set the position off screen
	m_position = sf::Vector2f(900.0f, 400.0f);
	m_countdownSprite.setPosition(m_position);
	m_countdownSprite.setOrigin(m_countdownRec[0].width / 2, m_countdownRec[0].height / 2);

	m_finishedCountingDown = false;
	m_timeCounter = 0.0;
	m_interpolation = 0.0f;
	m_alpha = 255.0f; 
	m_recIndex = 0;
}

/// <summary>
/// 
/// </summary>
/// <returns>Returns current state of count down</returns>
bool RaceCountdown::getFinishedCountingDown()
{
	return m_finishedCountingDown;
}