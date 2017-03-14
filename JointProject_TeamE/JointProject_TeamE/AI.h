#ifndef AI_H
#define AI_H

#include "Racer.h"
#include <SFML\Graphics.hpp>
#include "MathUtility.h"

struct Waypoint;

class AI : public Racer
{
public:
	AI();
	~AI();

	void update(float dt);
	void setWayPoints(std::vector<Waypoint> &m_wayPoints);

protected:
	std::vector<Waypoint> *m_wayPoints;
	unsigned int m_currentNode;
	sf::Vector2f m_steering;

	sf::Vector2f pathFollowing();
};

#endif