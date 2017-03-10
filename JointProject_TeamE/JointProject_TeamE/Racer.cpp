#include "Racer.h"

/// <summary>
/// Default constructor for a racer object
/// </summary>
Racer::Racer()
{
	
}

/// <summary>
/// Default destructor for a racer object
/// </summary>
Racer::~Racer()
{
}

/// <summary>
/// Render the racers car and name
/// </summary>
/// <param name="window"></param>
void Racer::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

/// <summary>
/// Sets the current car of the racer via pointer
/// </summary>
void Racer::setCar()
{
	m_position.x = 300.f;
	m_position.y = 300.f;
	m_sprite.setTexture(g_resourceMgr.textureHolder["CarTexture"]);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f));
	m_acceleration = 200.f;
	m_deceleration = 200.f;
	m_speed = 15.f;
	m_turnRate = 90.f;
}

/// <summary>
/// Sets the current position of the racer
/// </summary>
/// <param name="positonIn">The position the racer is to have</param>
void Racer::setPosition(sf::Vector2f positonIn)
{
	m_position = positonIn;
}

/// <summary>
/// Sets the current rotation of the racer
/// </summary>
/// <param name="rotationIn">The rotation the racer is to have</param>
void Racer::setRotation(float rotationIn)
{
	m_currentRotation = rotationIn;
}

void Racer::calMovement(float dt)
{
	m_sprite.setRotation(m_currentRotation);
	float addOnTotal = m_velocity * dt + 0.5f * m_acceleration * dt * dt; // formula: s = (ut) + (0.5 * at²)
	float xPosAddOn = addOnTotal * std::cos(degreesToRad(m_currentRotation));
	float yPosAddOn = addOnTotal * std::sin(degreesToRad(m_currentRotation));
	m_position.x += xPosAddOn;
	m_position.y += yPosAddOn;
	m_sprite.setPosition(m_position);
}

void Racer::turnLeft(float dt)
{
	m_currentRotation -= m_turnRate * dt;
}

void Racer::turnRight(float dt)
{
	m_currentRotation += m_turnRate * dt;
}

void Racer::accelerate(float dt)
{
	m_velocity += m_acceleration * dt;
}

void Racer::decelerate(float dt)
{
	m_velocity -= m_deceleration * dt;
}




