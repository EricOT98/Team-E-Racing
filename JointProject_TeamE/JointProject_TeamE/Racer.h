/// <summary>
/// Author: Eric O' Toole and Liam Hickey
/// Description: A basic class for a racer object that will contain a car and name
/// thus allowing multiple different racers to be processed the same way
/// 
/// Date Started: 09/03/17
/// Time Taken: 20 minutes
/// Known Errors:No known Errors
/// TODO: Implement car class to allow
/// </summary>

#ifndef RACER_H
#define RACER_H

#include "ResourceManager.h"
#include <SFML\Graphics.hpp>
#include "MathUtility.h"
#include <Thor\Particles.hpp>
#include "Thor\Animations.hpp"
#include <Thor\Math.hpp>

class Racer
{
public:
	Racer();
	~Racer();
	
	virtual void update(float dt) = 0;
	void render(sf::RenderWindow & window);
	void setCar();
	void setPosition(sf::Vector2f positionIn);
	void setRotation(float rotationIn);
	sf::Vector2f getPosition();
	float getRotation();

	void setFrictionHigh();
	void setFrictionLow();

protected:
	// Protected Functions
	void turnLeft(float dt, float percentageTurn);
	void turnRight(float dt, float percentageTurn);
	void accelerate(float dt, float percentageThrottle);
	void decelerate(float dt, float percentageBrake);
	void calMovement(float dt);

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
	float m_velocity;
	float m_currentAcceleration;
	sf::Vector2f m_position;
	
	sf::Sprite m_sprite;
	sf::Texture m_tireTexture;
	thor::ParticleSystem m_tireTracks;
	thor::UniversalEmitter m_trackEmmiter;
	sf::Clock m_clock;
	unsigned int m_index = 0;
};

#endif
