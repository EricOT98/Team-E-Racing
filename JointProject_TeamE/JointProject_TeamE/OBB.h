/// <summary>
/// @Author: Darren Sweeney
/// @version: 1.00
/// </summary>

#ifndef OBB_H
#define OBB_H

#include <SFML\Graphics.hpp>
#include "MathUtility.h"

/// Oriented Bounding Box (OBB) handles collison test between OBB bounding volumes.
/// 
/// Oriented Bounding Box (OBB) handles collison test between OBB bounding volumes.
/// Provides methods for debug rendering the box volume and updating the bounding volume.
class OBB
{
public:
	OBB();
	OBB(const sf::Vector2f &center, const float width, const float height, double angle);
	bool intersects(const OBB &obb) const;
	void construct(sf::Vector2f &center, sf::Vector2f &size, float angle);
	void debugRender(sf::RenderWindow &window);

private:
	sf::Vector2f corner[4];
	sf::Vector2f axis[2];
	float origin[2];

	// For debug rendering the OBB volume.
	sf::Vector2f position;
	sf::Vector2f size;
	float rotation;

	void computeAxis();
	bool overlapsOnAixs(const OBB& OBB) const;
};

#endif