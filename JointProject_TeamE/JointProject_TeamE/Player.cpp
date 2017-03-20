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
	if (KeyboardHandler::GetInstance()->IsKeyDown(sf::Keyboard::Key::Right))
	{
		turnRight(dt / 1000.0f, 80.0f);
	}
	else if (KeyboardHandler::GetInstance()->IsKeyDown(sf::Keyboard::Key::Left))
	{
		turnLeft(dt / 1000.0f, 80.0f);
	}

	if (KeyboardHandler::GetInstance()->IsKeyDown(sf::Keyboard::Key::Down))
	{
		decelerate(dt / 1000.f, 100.0f);
	}
	else if (KeyboardHandler::GetInstance()->IsKeyDown(sf::Keyboard::Key::Up))
	{
		accelerate(dt / 1000.f, 100.0f);
	}
	//@Projectile
	/*if (KeyboardHandler::GetInstance()->IsKeyDown(sf::Keyboard::Key::Space))
	{
		fire();
	}*/
	calMovement(dt / 1000.f);

	// Construct a new OBB when the player is moving
	m_boundingBox.construct(m_position, sf::Vector2f(m_sprite.getLocalBounds().width * m_sprite.getScale().x,
		m_sprite.getLocalBounds().height * m_sprite.getScale().y), m_currentRotation);
}