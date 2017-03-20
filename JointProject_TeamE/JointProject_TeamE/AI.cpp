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

	velocity = truncate(velocity + m_steering, SPEED);
	m_position = m_position + velocity;
	
	double angle = atan2(velocity.y, velocity.x) / PI * 180;

	m_sprite.setRotation(angle);
	m_sprite.setPosition(m_position);

	//std::cout << "Current Node: " << m_currentNode << std::endl;
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

		if (distance(target, m_position) < WAYPOINT_RADIUS)
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