#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include <SFML\Window\Keyboard.hpp>

/// Managers the input from the keyboard
/// 
/// Using a singeton pattern for the KeyboardHandler which keeps
/// track of the keys pressed and released.
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