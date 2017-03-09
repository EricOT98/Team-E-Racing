/// <summary>
/// @author: eric O' Toole
/// @version: 1.00
/// </summary>
#ifndef CAR_H
#define CAR_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "MathUtility.h"
#include "Thor\Vectors.hpp"
//#include "XboxController.h" this line gives a linker error

enum class Type {CAR1, CAR2, CAR3, CAR4, CAR5, CAR6 };

class Car
{
public:
	Car(std::string name, int maxSpeed, int friction, int turnRate, sf::Vector2f acceleration, sf::Vector2f position);
	~Car();

	void initialise();
	void update();
	void render(sf::RenderWindow & window);
	void processInput(sf::Event & e);


protected:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	Type m_type;
	std::string m_name;
	int m_speed;
	int m_maxSpeed;
	int m_maxReverseSpeed;
	int m_friction;
	int m_turnRate;
	int m_rotation;
	float m_rotationRads;
	int m_accelerationStep;
	int m_brakingStep;
	sf::Vector2f m_acceleration;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;

	void accelerate();
	void decelerate();
	void turnLeft();
	void turnRight();
};
#endif
