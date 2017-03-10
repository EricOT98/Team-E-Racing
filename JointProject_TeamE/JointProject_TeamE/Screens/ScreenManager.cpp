#include "ScreenManager.h"

ScreenManager::ScreenManager() { }

ScreenManager::~ScreenManager() 
{
	delete m_mainMenu;
	delete m_optionsMenu;
	delete m_soundOptions;
}

void ScreenManager::init()
{
	m_mainMenu = new MainMenu();
	m_optionsMenu = new Options();
	m_soundOptions = new SoundOptions();
}

void ScreenManager::update()
{
	m_mainMenu->update();
	m_optionsMenu->update();
	m_soundOptions->update();
}

void ScreenManager::render(sf::RenderWindow &window)
{
	//m_mainMenu->render(window);
	//m_optionsMenu->render(window);
	m_soundOptions->render(window);
}

void ScreenManager::processInput(XboxController &controller)
{
	//m_mainMenu->processInput(controller);
	//m_optionsMenu->processInput(controller);
	m_soundOptions->processInput(controller);
}