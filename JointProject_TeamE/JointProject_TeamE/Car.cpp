#include "Car.h"

Car::Car(std::string name, int maxSpeed, int friction, int turnRate, sf::Vector2f acceleration, sf::Vector2f position) :
	m_name(name),
	m_maxSpeed(maxSpeed),
	m_friction(friction), 
	m_turnRate(turnRate),
	m_acceleration(acceleration),
	m_position(position)
{
	m_texture.loadFromFile("test.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
}

Car::~Car()
{
}

void Car::initialise()
{
	m_maxReverseSpeed = -(m_maxSpeed / 2);
}

void Car::update()
{
	m_rotationRads = degreesToRad(m_rotation);
	sf::Vector2f direction = sf::Vector2f(std::cos(m_rotationRads), std::sin(m_rotationRads));
	direction = thor::unitVector(direction);
	m_velocity += (static_cast<float>(m_speed) * direction);
}

void Car::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

void Car::processInput(sf::Event & e)
{
}

void Car::accelerate()
{
	if (m_speed < m_maxSpeed)
	{
		m_speed += m_accelerationStep;
	}
	else
	{
		m_speed = m_maxSpeed;
	}
}

void Car::decelerate()
{
	if (m_speed > m_maxReverseSpeed)
	{
		m_speed -= m_brakingStep;
	}
	else
	{
		m_speed = m_maxReverseSpeed;
	}
}

void Car::turnLeft()
{
	if (m_rotation > 0)
	{
		m_rotation -= m_turnRate;
	}
	else
	{
		m_rotation = 359;
	}
}

void Car::turnRight()
{
	if (m_rotation < 359)
	{
		m_rotation += m_turnRate;
	}
	else
	{
		m_rotation = 0;
	}
}
