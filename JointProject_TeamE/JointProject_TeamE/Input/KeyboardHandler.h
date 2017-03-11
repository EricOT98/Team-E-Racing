#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include <SFML\Window\Keyboard.hpp>

class KeyboardHandler
{
private:
	KeyboardHandler();

public:
	bool m_keysDown[sf::Keyboard::Key::KeyCount];
	bool m_keysUp[sf::Keyboard::Key::KeyCount];

	static KeyboardHandler *GetInstance();
	bool IsKeyPressed(int key);
	bool IsKeyDown(int key);
};

#endif