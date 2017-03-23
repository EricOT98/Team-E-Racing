/// <summary>
/// Author: Eric O' Toole and Liam Hickey
/// Description: A basic class for a racer object that will contain a car and name
/// thus allowing multiple different racers to be processed the same way
/// 
/// Date Started: 09/03/17
/// Time Taken: 20 minutes
/// Known Errors:No known Errors
/// </summary>

#ifndef RACER_H
#define RACER_H

#include "ResourceManager.h"
#include <SFML\Graphics.hpp>
#include "MathUtility.h"
#include <Thor\Particles.hpp>
#include "Thor\Animations.hpp"
#include <Thor\Math.hpp>
#include "OBB.h"
#include "Projectile.h"
#include "SpotLight.h"
#include "LevelLoader.h"

/// <summary>
/// Racer base class used to process behaviour of both the Player and the AI
/// </summary>
class Racer
{
public:
	Racer();
	~Racer();
	virtual void update(float dt) = 0;
	void render(sf::RenderWindow & window);
	void setCar(CarData carData);
	void setPosition(sf::Vector2f positionIn);
	void setRotation(float rotationIn);
	sf::Vector2f getPosition();
	float getRotation();
	void resolveCollision();
	void resolveRacerCollision(sf::Vector2f positionIn);
	void setFrictionHigh();
	void setFrictionLow();
	void fire();
	int getNumProjectiles();
	void setCheckPoint();
	void setWayPoints(std::vector<Waypoint> &wayPoints);
	void checkNodes(); 
	int getLap();
	void setRadius(float radiusIn);
	void projectileCollision();
	void setAlive(bool alive);

	// Public members
	OBB m_boundingBox;
	SpotLight m_spotLight;
	std::vector<std::unique_ptr<Projectile>> m_projectiles;
protected:
	// Protected Functions
	void turnLeft(float dt, float percentageTurn);
	void turnRight(float dt, float percentageTurn);
	void accelerate(float dt, float percentageThrottle);
	void decelerate(float dt, float percentageBrake);
	void calMovement(float dt);
	void positionTracks();

	// Caar Attributes Copied Over
	float m_speed;
	float m_deceleration;
	float m_acceleration;
	float m_turnRate;
	float m_frictionHigh;
	float m_frictionLow;
	float m_currentFriction;

	// Changeable Attributes
	float m_currentRotation;
	float m_lastRotation;
	float m_velocity;
	float m_currentAcceleration;
	sf::Vector2f m_position;
	sf::Vector2f m_lastPosition;
	sf::Vector2f m_direction;
	sf::Sprite m_sprite;
	bool m_alive;

	// THOR Particle Emitter attributes for skid marks
	sf::Texture m_tireTexture;
	thor::ParticleSystem m_tireTracks;
	thor::UniversalEmitter m_trackEmmiter;
	thor::UniversalEmitter m_trackEmmiter2;
	thor::UniversalEmitter m_smokeEmmiterLeft;
	sf::Clock m_clock;
	unsigned int m_index = 0;
	int numProjectiles;

	// Attributes for the tracking of the Racer's laps
	int m_lapsCompleted;
	std::vector<Waypoint> *m_wayPoints;
	unsigned int m_currentNode;
	float m_radius;
	bool m_lastWayPointHit;

	// <Test>

	sf::Vector2f m_currentAccelerationVec;
	sf::Vector2f m_currentVelocityVec;
	sf::Vector2f m_racerCollisionVec;

	// </Test>
	
};

#endif
