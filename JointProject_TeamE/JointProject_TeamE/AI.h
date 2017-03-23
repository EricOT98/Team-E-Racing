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
	void reset();

protected:
	sf::Vector2f m_steering;
	const float WAYPOINT_RADIUS = 50.0f;
	const float MAX_SPEED = 5.0f;
	float m_speed;

};

#endif