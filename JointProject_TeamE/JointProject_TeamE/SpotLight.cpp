#include "SpotLight.h"

SpotLight::SpotLight() { };

/// <summary>
/// Initalizes the spotlight
/// </summary>
/// <param name="position">The position of the spot light</param>
/// <param name="size">Size of lightmap texture</param>
/// <param name="color">The color tone of the light map</param>
SpotLight::SpotLight(sf::Vector2f position, sf::Vector2f size, sf::Color color)
	: m_position(position), m_size(size), m_color(color)
{

}

void SpotLight::update(sf::Vector2f &pos)
{
	m_position = pos;
}