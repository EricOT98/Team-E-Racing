#include "AI.h"

/// <summary>
/// Default constructor for the AI
/// </summary>
AI::AI()
	: m_steering() 
{
	m_position = sf::Vector2f(0.0f, 0.0f);

	srand(time(NULL));

	m_speed = rand() % int(MAX_SPEED) + 2;
}

/// <summary>
/// Destructor function for the AI
/// </summary>
AI::~AI() { }

/// <summary>
/// Update function to allow the AI to decide its own path through the track
/// </summary>
/// <param name="dt">delta time since last update</param>
void AI::update(float dt)
{
	float acceleration = m_wayPoints->at(m_currentNode).m_speed; // Check what the waypoints speed is
	if (acceleration > 0) // Decide the AI's acceleration based off of this value
	{
		accelerate(dt, acceleration);
	}
	else
	{
		decelerate(dt, acceleration);
	}

	sf::Vector2f vectorToNode = (m_wayPoints->at(m_currentNode).m_position - m_position); // Find the vector from the racer to the current node / waypoint
	float angle = (atan2(vectorToNode.y, vectorToNode.x) / PI * 180) - m_currentRotation; // Calculate how much the AI needs to turn
	if (angle < -180) // If else makes sure the AI does not turn the long way around to the target node
	{
		angle += 360;
	}
	else if (angle > 180)
	{
		angle -= 360;
	}
	if (angle < -1.f) // Decide whether we need to turn left or right
	{
		turnLeft(dt / 1000.f, 100);
	}
	else if (angle > 1.f)
	{
		turnRight(dt / 1000.f, 100);
	}
	checkNodes(); // Check if the AI has hot their node
	calMovement(dt / 1000.f); // Calculate the movement of the AI

	// Construct a new OBB when the player is moving
	m_boundingBox.construct(m_position, sf::Vector2f(m_sprite.getLocalBounds().width * m_sprite.getScale().x,
		m_sprite.getLocalBounds().height * m_sprite.getScale().y), m_currentRotation);

	// Update the car's headlight
	m_spotLight.update(m_position + sf::Vector2f(40.0f * cos(degreesToRad(m_currentRotation)),
														40.0f * sin(degreesToRad(m_currentRotation))));
}

/// <summary>
/// Reset method  for the AI class
/// </summary>
void AI::reset() {}