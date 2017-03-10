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

protected:
	// Protected Functions
	void turnLeft(float dt);
	void turnRight(float dt);
	void accelerate(float dt);
	void decelerate(float dt);
	void calMovement(float dt);

	// Caar Attributes Copied Over
	float m_speed;
	float m_deceleration;
	float m_acceleration;
	float m_turnRate;

	// Changeable Attributes
	float m_currentRotation;
	float m_velocity;
	sf::Vector2f m_position;
	
	sf::Sprite m_sprite;


};

#endif
