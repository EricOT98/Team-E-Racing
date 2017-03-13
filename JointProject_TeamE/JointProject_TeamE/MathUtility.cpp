#include "MathUtility.h"

/// <summary>
/// Returns a position that is between start position and end position
/// based on the interpolate value form [0, 1]
/// </summary>
/// <param name="startPos">The inital start position</param>
/// <param name="endPos">The final target position</param>
/// <param name="interpolate">Number from [0, 1] of far along the transition is</param>
/// <returns>A position between start and end based on the interpolate value</returns>
sf::Vector2f lerp(sf::Vector2f &startPos, sf::Vector2f &endPos, float interpolate)
{
	return sf::Vector2f((1.0f - interpolate) * startPos.x + (interpolate * endPos.x),
		(1.0f - interpolate) * startPos.y + (interpolate * endPos.y));
}

/// <summary>
/// Converts a value from radians to degrees
/// </summary>
/// <param name="radians">The value to convert</param>
/// <returns>Return a value in degrees</returns>
float radiansToDeg(float radians)
{
	return radians * 180.0f / PI;
}

/// <summary>
/// Converts a value from degrees to radians
/// </summary>
/// <param name="degrees">The value to convert</param>
/// <returns>Return a value in radians</returns>
float degreesToRad(float degrees)
{
	return degrees * PI / 180.0f;
}

/// <summary>
/// 
/// </summary>
/// <param name="image"></param>
/// <param name="iterations"></param>
void rotateImage90(sf::Image & image, int iterations)
{
	sf::Image result;
	result.create(image.getSize().y, image.getSize().x, sf::Color::White);
	for (int iterator = 0; iterator < iterations; iterator++)
	{
		for (int i = 0; i < image.getSize().x; i++)
		{
			for (int j = 0; j < image.getSize().y; j++)
			{
				result.setPixel(image.getSize().x - j - 1, i, image.getPixel(i, j));
			}
		}
		image = result;
	}
}