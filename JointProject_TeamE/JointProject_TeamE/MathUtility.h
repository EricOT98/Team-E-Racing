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

float lerpFloat(float start, float end, float interpolate);

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

/// <summary>
/// Calculates the distance between two points
/// </summary>
float distance(sf::Vector2f &pos0, sf::Vector2f &pos1);

float length(sf::Vector2f &v);

sf::Vector2f truncate(sf::Vector2f &v, float const num);

sf::Vector2f unitVector(sf::Vector2f &v);

float dot(const sf::Vector2f &v1, const sf::Vector2f &v2);

float squaredLenght(const sf::Vector2f &vec);

#endif