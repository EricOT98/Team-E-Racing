#include "ScreenManager.h"

ScreenManager::ScreenManager() { }

ScreenManager::~ScreenManager() { }

void ScreenManager::init()
{
	m_mainMenu = new MainMenu();
}

void ScreenManager::update()
{
	m_mainMenu->update();
}

void ScreenManager::render(sf::RenderWindow &window)
{
	m_mainMenu->render(window);
}

void ScreenManager::processInput(XboxController &controller)
{
	m_mainMenu->processInput(controller);
}