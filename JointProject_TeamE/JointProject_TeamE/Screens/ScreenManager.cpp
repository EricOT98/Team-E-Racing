#include "ScreenManager.h"

ScreenManager::ScreenManager() { }

ScreenManager::~ScreenManager() 
{
	delete m_mainMenu;
	delete m_optionsMenu;
	delete m_soundOptions;
	delete m_difficultyScreen;
	delete m_helpScreen;
	delete m_pauseScreen;
	delete m_confirmationScreen;
}

void ScreenManager::init()
{
	m_mainMenu = new MainMenu();
	m_optionsMenu = new Options();
	m_soundOptions = new SoundOptions();
	m_difficultyScreen = new DifficultyScreen();
	m_helpScreen = new HelpScreen();
	m_pauseScreen = new PauseScreen();
	m_confirmationScreen = new ConfirmationScreen();
}

void ScreenManager::update()
{
	switch (Screen::currentGameState)
	{
	case GameScreenState::MainMenuScreen:
		m_mainMenu->update();
		break;

	case GameScreenState::OptionsScreen:
		m_optionsMenu->update();
		break;

	case GameScreenState::SoundOptionsScreen:
		m_soundOptions->update();
		break;

	case GameScreenState::DifficultyScreen:
		m_difficultyScreen->update();
		break;

	case GameScreenState::QuitConfirmation:
		m_confirmationScreen->update();
		break;
	default:
		break;
	}
}

void ScreenManager::render(sf::RenderWindow &window)
{
	switch (Screen::currentGameState)
	{
	case GameScreenState::MainMenuScreen:
		m_mainMenu->render(window);
		break;

	case GameScreenState::OptionsScreen:
		m_optionsMenu->render(window);
		break;

	case GameScreenState::SoundOptionsScreen:
		m_soundOptions->render(window);
		break;

	case GameScreenState::DifficultyScreen:
		m_difficultyScreen->render(window);
		break;

	case GameScreenState::QuitConfirmation:
		m_confirmationScreen->render(window);
		break;

	default:
		break;
	}
}

void ScreenManager::processInput(XboxController &controller)
{
	switch (Screen::currentGameState)
	{
	case GameScreenState::MainMenuScreen:
		m_mainMenu->processInput(controller);
		break;

	case GameScreenState::OptionsScreen:
		m_optionsMenu->processInput(controller);
		break;

	case GameScreenState::SoundOptionsScreen:
		m_soundOptions->processInput(controller);
		break;

	case GameScreenState::DifficultyScreen:
		m_difficultyScreen->processInput(controller);
		break;

	case GameScreenState::QuitConfirmation:
		m_confirmationScreen->processInput(controller);
		break;

	default:
		break;
	}
}