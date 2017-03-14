#include "ScreenManager.h"

/// <summary>
/// Default Constructor for the screen manager class
/// </summary>
ScreenManager::ScreenManager() : m_gameState(GameState::SplashScreen)
{
	//m_backgroundSprite.setTexture(*g_resourceMgr.getBackgroundTexture());
}

/// <summary>
/// Default destructor function for the ScreenManager Class
/// </summary>
ScreenManager::~ScreenManager()
{
	for (Screen *screen : screens)
	{
		delete screen; // Delete screens so as to prevent a memory leak
	}
	screens.clear(); // Clear the std::vector just in case
}

/// <summary>
/// update function updtes the current screen based off of the current game state
/// </summary>
/// <param name="controller">The controller to be passed to each screen when updating</param>
void ScreenManager::update(XboxController &controller)
{
	// We use the variable m_currentScreen so as we don't have to loop through the vector again when rendering
	for (m_currentScreen = 0; m_currentScreen < screens.size(); m_currentScreen++)
	{
		if (screens.at(m_currentScreen)->getGameState() == m_gameState) // Check if the game state of the screen matches the current game state
		{
			screens.at(m_currentScreen)->update(controller); // Update the current screen
			GameState nextState = screens.at(m_currentScreen)->getNextGameState();
			if (nextState != m_gameState) // Check if the screen wants to switch game states
			{
				if (GameState::Options == m_gameState)
				{
					for (Screen * screen : screens)
					{
						screen->setColors(); // We reset the colours of every screen if we have come from the options screen
						if (screen->getGameState() == GameState::GamePlay)
						{
							screen->reset(); // We need to also reset the game if this is the case
						}
					}
				}
				m_gameState = nextState; // Set the current game state
				screens.at(m_currentScreen)->resetNextGameState(); // Reset the game state of the net screen member of the current screen
			}
			break; // Break so as not to continue with the loop
		}
	}
}

/// <summary>
/// render function draws the current screen which is decided in the update function
/// </summary>
/// <param name="window">The render window used for drawing the screens</param>
void ScreenManager::render(sf::RenderWindow& window)
{
	
	if (m_currentScreen < screens.size())
	{	
		if (screens.at(m_currentScreen)->getGameState() != GameState::SplashScreen)
		{
			window.draw(m_backgroundSprite); // Only draw the background sprite if the screen currently beinng drawn is not the splash screen
		}
		screens.at(m_currentScreen)->render(window); // Draw the current screen
	}
}

/// <summary>
/// add function used to add a pointer to a screen onto the screen manager object
/// </summary>
/// <param name="screenIn">A pointer to a screen declared on the heap</param>
void ScreenManager::add(Screen * screenIn)
{
	screens.push_back(screenIn); // Add the screen to the vector
}