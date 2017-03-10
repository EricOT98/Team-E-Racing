#include "ScreenManager.h"

ScreenManager::ScreenManager() { }

ScreenManager::~ScreenManager() 
{
	delete m_mainMenu;
	delete m_optionsMenu;
}

void ScreenManager::init()
{
	m_mainMenu = new MainMenu();
	m_optionsMenu = new Options();
}

void ScreenManager::update()
{
	m_mainMenu->update();
	m_optionsMenu->update();
}

void ScreenManager::render(sf::RenderWindow &window)
{
	//m_mainMenu->render(window);
	m_optionsMenu->render(window);
}

void ScreenManager::processInput(XboxController &controller)
{
	//m_mainMenu->processInput(controller);
	m_optionsMenu->processInput(controller);
}