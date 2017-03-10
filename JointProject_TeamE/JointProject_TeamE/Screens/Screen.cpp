#include "Screen.h"

/// <summary>
/// Initalizes the m_active to false which represent the screen state
/// </summary>
Screen::Screen()
	: m_active(false)
{

}

/// <summary>
/// Virtual deconstructor so the dervied class deconstrcutor is called 
/// </summary>
Screen::~Screen()
{

}

/// <summary>
/// Virtual method to override for custum screen updating
/// </summary>
void Screen::update()
{

}

/// <summary>
/// Virtual method to override for custum screen rendering
/// </summary>
void Screen::render()
{

}

/// <summary>
/// 
/// </summary>
/// <param name="event">The events happened inside the window</param>
void Screen::processInput(sf::Event &event)
{

}