/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef MATH_UTIL
#define MATH_UTIL

#include <SFML\Graphics.hpp>
#include <iostream>

#define PI 3.14159265

/// <summary>
/// Simple utility for using a LERP function
/// </summary>
sf::Vector2f lerp(sf::Vector2f &startPos, sf::Vector2f &endPos, float interpolate);

/// <summary>
/// Converts from radians to degrees
/// </summary>
float radiansToDeg(float radians);

/// <summary>
/// Converts from degrees to radians
/// </summary>
float degreesToRad(float degrees);

/// <summary>
/// Rotates the pixels of an image around by 90 degrees
/// </summary>
void rotateImage90(sf::Image & image, int iterations);

#endif