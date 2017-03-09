#include "Player.h"

/// <summary>
/// Default constructor for the player object
/// </summary>
Player::Player()
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
void Player::update()
{
}

/// <summary>
/// Render the players car and name
/// </summary>
/// <param name="window"></param>
void Player::render(sf::RenderWindow & window)
{
}

/// <summary>
/// Process input from the player to control the car
/// </summary>
/// <param name="e"></param>
void Player::processInput(sf::Event & e)
{
}

/// <summary>
/// Sets the players position in the race order ie 1st,2nd etc
/// </summary>
/// <param name="pos"></param>
void Player::setRacePosition(int pos)
{
	m_racePosition = pos;
}
