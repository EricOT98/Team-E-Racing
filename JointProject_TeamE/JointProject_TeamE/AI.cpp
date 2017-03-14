#include "AI.h"

AI::AI()
	: m_currentNode(0), m_steering() 
{
	m_position = sf::Vector2f(0.0f, 0.0f);
}

AI::~AI() { }

sf::Vector2f velocity = sf::Vector2f();

void AI::update(float dt)
{
	sf::Vector2f vectorToNode = pathFollowing();

	m_steering = sf::Vector2f();
	m_steering = m_steering + pathFollowing();

	m_steering = truncate(m_steering, 1.1f);
	m_steering = m_steering / 1.0f;

	velocity = truncate(velocity + m_steering, 1.0f);
	m_position = m_position + velocity;
	
	auto dest = atan2(-1 * velocity.y, -1 * velocity.x) / PI * 180 + 180;

	auto currentRotation = m_currentRotation;

	if (std::round(currentRotation - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}
	else if ((static_cast<int>(std::round(dest - currentRotation + 360))) % 360 < 180)
	{
		// rotate clockwise
		m_currentRotation = static_cast<int>((m_currentRotation) + 1) % 360;
	}
	else
	{
		// rotate anti-clockwise
		m_currentRotation -= 1;
	}

	m_sprite.setRotation(m_currentRotation);
	m_sprite.setPosition(m_position);

	std::cout << "Current Node: " << m_currentNode << std::endl;
}

void AI::setWayPoints(std::vector<Waypoint> &wayPoints)
{
	m_wayPoints = &wayPoints;
}

sf::Vector2f AI::pathFollowing()
{
	sf::Vector2f target;

	if (m_wayPoints->size() != 0)
	{
		target = m_wayPoints->at(m_currentNode).m_position;

		// NOTE(Darren): For now all nodes have a radius of 10.0f, we can change that if needs be.
		if (distance(target, m_position) < 20.0f)
		{
			m_currentNode++;

			if (m_currentNode >= m_wayPoints->size())
			{
				m_currentNode = 0;
			}
		}
	}

	sf::Vector2f direction = m_wayPoints->at(m_currentNode).m_position - m_position;

	return direction;
}