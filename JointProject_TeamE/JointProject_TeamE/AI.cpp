#include "AI.h"

AI::AI()
	: m_steering() 
{
	m_position = sf::Vector2f(0.0f, 0.0f);

	srand(time(NULL));

	m_speed = rand() % int(MAX_SPEED) + 2;
}

AI::~AI() { }

void AI::update(float dt)
{
	sf::Vector2f vectorToNode = pathFollowing();

	m_steering = sf::Vector2f(); 
	m_steering = m_steering + vectorToNode;

	m_steering = truncate(m_steering, 1.1f);
	m_steering = m_steering / 1.0f;

	m_velocity = truncate(m_velocity + m_steering, m_speed);
	m_position = m_position + m_velocity;
	
	double angle = atan2(m_velocity.y, m_velocity.x) / PI * 180;

	m_sprite.setRotation(angle);
	m_sprite.setPosition(m_position);

	// Construct a new OBB when the player is moving
	m_boundingBox.construct(m_position, sf::Vector2f(m_sprite.getLocalBounds().width * m_sprite.getScale().x,
		m_sprite.getLocalBounds().height * m_sprite.getScale().y), m_currentRotation);

	m_spotLight.update(m_position + sf::Vector2f(40.0f * cos(degreesToRad(angle)),
														40.0f * sin(degreesToRad(angle))));
}

void AI::reset()
{
	m_velocity = sf::Vector2f();
	m_steering = sf::Vector2f();
}

sf::Vector2f AI::pathFollowing()
{
	sf::Vector2f target;

	if (m_wayPoints->size() != 0)
	{
		target = m_wayPoints->at(m_currentNode).m_position;
		m_radius = rand() % int(WAYPOINT_RADIUS) + 5;
		checkNodes();
	}

	sf::Vector2f direction = m_wayPoints->at(m_currentNode).m_position - m_position;

	return direction;
}