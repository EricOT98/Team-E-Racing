#include "SplashScreen.h"

/// <summary>
/// Create a splash screen object and set the object to start fading in a texture
/// aswell as loading a movie with the SFEmovie libraries
/// </summary>
SplashScreen::SplashScreen() : Screen(GameState::SplashScreen)
{
	m_fadeIn = true;
	m_foreground.setPosition(0, 0);
	m_fadeTime = 2;
	m_alphaStep = (MAX_ALPHA / m_fadeTime) / 60.0f;
	try
	{
		m_intro.openFromFile("Resources/Movies/IntroAnimation.mov");
	}
	catch(std::exception e)
	{
		std::cout << typeid(*this).name() << std::endl;
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	m_intro.setPosition(0, 0);
	m_foreground.setSize(sf::Vector2f(800, 600));
	m_foreground.setTexture(&g_resourceMgr.textureHolder["objects"]);
	m_foregroundColor = m_foreground.getFillColor();
	int a = m_foregroundColor.a;
	m_foreground.setFillColor(m_foregroundColor);
	m_currentAlpha = 0;
	m_intro.fit(0, 0, 800, 600);
	m_skip = false;
}

/// <summary>
/// Clear all elemets of the splashscreens gui
/// </summary>
SplashScreen::~SplashScreen()
{
	m_gui.clear();
}

/// <summary>
/// Fade the text in every update and check for button presses to skip the intros
/// </summary>
/// <param name="controller">The xbox 360 controller to process player input</param>
void SplashScreen::update(XboxController & controller)
{
	if (m_fadeIn)
	{
		m_currentAlpha += m_alphaStep;
		m_foregroundColor.a = m_currentAlpha;
		m_foreground.setFillColor(m_foregroundColor);
		if (m_currentAlpha >= MAX_ALPHA)
		{
			m_intro.play();
			m_playing = true;
			m_fadeIn = false;
		}
	}
	if (m_playing)
	{
		m_intro.update();
		if (!m_skip)
		{
			for (unsigned int i = 0; i < 10; i++)
			{
				if (controller.isButtonPressed(i))
				{
					m_intro.pause();
					m_skip = true;
					break;
				}
			}
		}
		if (m_intro.getStatus() == sfe::Status::Paused || m_intro.getStatus() == sfe::Status::Stopped)
		{
			transOut(GameState::MainMenu);
		}
	}
}

/// <summary>
/// Render the texture if the movie is not playing
/// else render the mvie
/// </summary>
/// <param name="window"></param>
void SplashScreen::render(sf::RenderWindow & window)
{
	if (m_playing)
	{
		window.draw(m_intro);
	}
	else
	{
		window.draw(m_foreground);
	}
}

/// <summary>
/// reset the current screen to it's defaults
/// </summary>
void SplashScreen::reset()
{
	m_fadeIn = true;
	m_playing = false;
	m_skip = false;
	m_currentAlpha = 0;
}
