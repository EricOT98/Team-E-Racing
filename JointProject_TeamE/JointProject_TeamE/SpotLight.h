/// <summary>
/// @Author: Darren Sweeney
/// @version: 1.00
/// </summary>

#ifndef LIGHT_H
#define LIGHT_H

#include <SFML\Graphics.hpp>

/// Provides a point light on screen
class SpotLight
{
public:
	SpotLight(sf::Vector2f position, sf::Vector2f size, sf::Color color);

	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::Color m_color;
};

#endif LIGHT_H