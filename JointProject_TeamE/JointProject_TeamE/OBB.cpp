#include "OBB.h"

OBB::OBB() { }

/// <summary>
/// Constructs a OBB volume.
/// </summary>
/// <param name="center">The origin of the box</param>
/// <param name="width">The width of the box</param>
/// <param name="height">The height of the box</param>
/// <param name="angle">Rotation in degress</param>
OBB::OBB(const sf::Vector2f& center, const float width, const float height, double angle)
	: position(center), rotation(angle), size(width, height)
{
	construct(position, size, rotation);
}

/// <summary>
/// Checks if a OBB intersects this OBB
/// </summary>
/// <param name="obb">A refernce to another OBB</param>
/// <returns>If this OBB and another intersect</returns>
bool OBB::intersects(const OBB &obb) const
{
	return overlapsOnAixs(obb) && obb.overlapsOnAixs(*this);
}

/// <summary>
/// Checks if a OBB overlaps on one axis of this
/// </summary>
/// <param name="obb"></param>
/// <returns></returns>
bool OBB::overlapsOnAixs(const OBB& obb) const 
{
	for (int a = 0; a < 2; ++a)
	{
		float t = dot(obb.corner[0], axis[a]);

		float tMin = t;
		float tMax = t;

		for (int c = 1; c < 4; ++c)
		{
			t = dot(obb.corner[c], axis[a]);

			if (t < tMin)
				tMin = t;
			else if (t > tMax)
				tMax = t;
		}

		if ((tMin > 1 + origin[a]) || (tMax < origin[a]))
			return false;
	}

	return true;
}

/// <summary>
/// Creates a OBB volume by computing the local axis and box corners.
/// </summary>
/// <param name="center">The origin of the OBB</param>
/// <param name="size">The size of the OBB, width and height</param>
/// <param name="angle">The angle of rotation of the OBB</param>
void OBB::construct(sf::Vector2f &center, sf::Vector2f &size, float angle)
{
	sf::Vector2f X(cos(degreesToRad(angle)), sin(degreesToRad(angle)));
	sf::Vector2f Y(-sin(degreesToRad(angle)), cos(degreesToRad(angle)));;

	X *= size.x / 2;
	Y *= size.y / 2;

	corner[0] = center - X - Y;
	corner[1] = center + X - Y;
	corner[2] = center + X + Y;
	corner[3] = center - X + Y;

	computeAxis();

	position = center;
	this->rotation = angle;
	this->size = sf::Vector2f(size.x, size.y);
}

/// <summary>
/// Calculates the local axis of the OBB.
/// </summary>
void OBB::computeAxis()
{
	axis[0] = corner[1] - corner[0];
	axis[1] = corner[3] - corner[0];

	for (int a = 0; a < 2; ++a) 
	{
		axis[a] /= squaredLenght(axis[a]);
		origin[a] = dot(corner[0], axis[a]);
	}
}

/// <summary>
/// Debug renders the bounding volume.
/// </summary>
/// <param name="window">A reference to a render window</param>
void OBB::debugRender(sf::RenderWindow &window)
{
	sf::RectangleShape obbShape;
	obbShape.setFillColor(sf::Color::Red);
	obbShape.setSize(size);
	obbShape.setPosition(position);
	obbShape.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
	obbShape.setRotation(rotation);

	window.draw(obbShape);
}