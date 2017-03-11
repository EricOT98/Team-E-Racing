#include "KeyboardHandler.h"

KeyboardHandler::KeyboardHandler()
{
	for (bool keyDown : m_keysDown)
		keyDown = false;

	for (bool keyUp : m_keysUp)
		keyUp = false;
}

KeyboardHandler *KeyboardHandler::GetInstance()
{
	static KeyboardHandler *instance = new KeyboardHandler();
	return instance;
}

bool KeyboardHandler::IsKeyPressed(int key)
{
	if (m_keysDown[key] && !m_keysUp[key])
	{
		m_keysUp[key] = true;
		return true;
	}

	return false;
}

bool KeyboardHandler::IsKeyDown(int key)
{
	if (m_keysDown[key])
	{
		return true;
	}

	return false;
}