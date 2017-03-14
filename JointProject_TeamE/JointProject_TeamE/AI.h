#ifndef AI_H
#define AI_H

#include "Racer.h"
#include <SFML\Graphics.hpp>

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
};

#endif