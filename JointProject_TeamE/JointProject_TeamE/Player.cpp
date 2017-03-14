#include "Player.h"

/// <summary>
/// Default constructor for the player object
/// </summary>
Player::Player(XboxController & controllerIn) : m_controller(controllerIn)
{
}

/// <summary>
/// Default destructor for player object
/// </summary>
Player::~Player()
{
}

/// <summary>
/// Initialise the players attributes, name etc.
/// </summary>
void Player::initialise()
{
}

/// <summary>
/// Update the players car and race position
/// </summary>
void Player::update(float dt)
{
	if (m_controller.getLeftStick().x > 20)
	{
		turnRight(dt / 1000.f, m_controller.getLeftStick().x);
	}
	else if (m_controller.getLeftStick().x < -20)
	{
		turnLeft(dt / 1000.f, -m_controller.getLeftStick().x);
	}
	if (m_controller.getLeftTrigger() > 30)
	{
		decelerate(dt / 1000.f, m_controller.getLeftTrigger());
	}
	else if (m_controller.getRightTrigger() < -30)
	{
		accelerate(dt / 1000.f, -m_controller.getRightTrigger());
	}

	// TODO: Take this out!! For debug use.
	if (KeyboardHandler::GetInstance()->IsKeyDown(sf::Keyboard::Key::Left))
	{
		turnRight(dt / 1000.0f, 155.5f);
	}
	else if (KeyboardHandler::GetInstance()->IsKeyDown(sf::Keyboard::Key::Right))
	{
		turnLeft(dt / 1000.0f, 155.5f);
	}

	if (KeyboardHandler::GetInstance()->IsKeyDown(sf::Keyboard::Key::Up))
	{
		decelerate(dt / 1000.f, 450.5f);
	}
	else if (KeyboardHandler::GetInstance()->IsKeyDown(sf::Keyboard::Key::Down))
	{
		accelerate(dt / 1000.f, 450.5f);
	}

	calMovement(dt / 1000.f);
}

