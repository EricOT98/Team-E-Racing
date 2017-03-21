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
#include "OBB.h"
#include "Projectile.h"
#include "SpotLight.h"

//auto & shader = std::unique_ptr<sf::Shader>(new sf::Shader());
//shader->loadFromFile("Resources/Shaders/crtShader.vert", "Resources/Shaders/crtShader.frag");
//shaderHolder.acquire("CRT", thor::Resources::fromFile<std::unique_ptr<sf::Shader>>("Resources/Shaders/crt_shader.vert", "Resources/Shaders/crt_shader.frag"));

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
	OBB m_boundingBox;
	SpotLight m_spotLight;
	std::vector<std::unique_ptr<Projectile>> m_projectiles;
	void resolveCollision();

	void setFrictionHigh();
	void setFrictionLow();
	void fire();
	int getNumProjectiles();
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
	thor::UniversalEmitter m_trackEmmiter2;
	thor::UniversalEmitter m_smokeEmmiterLeft;
	sf::Clock m_clock;
	unsigned int m_index = 0;
	int numProjectiles;

	std::unique_ptr<sf::Shader> m_rippleShader;
};

#endif
