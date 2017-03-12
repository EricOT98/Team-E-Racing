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
	m_mainMenu->update();
	m_optionsMenu->update();
	m_soundOptions->update();
	m_difficultyScreen->update();
	m_helpScreen->update();
	m_pauseScreen->update();
	m_confirmationScreen->update();
}

void ScreenManager::render(sf::RenderWindow &window)
{
	//m_mainMenu->render(window);
	//m_optionsMenu->render(window);
	//m_soundOptions->render(window);
	//m_difficultyScreen->render(window);
	//m_helpScreen->render(window);
	//m_pauseScreen->render(window);
	m_confirmationScreen->render(window);
}

void ScreenManager::processInput(XboxController &controller)
{
	//m_mainMenu->processInput(controller);
	//m_optionsMenu->processInput(controller);
	//m_soundOptions->processInput(controller);
	//m_difficultyScreen->processInput(controller);
	//m_helpScreen->processInput(controller);
	//m_pauseScreen->processInput(controller);
	m_confirmationScreen->processInput(controller);
}