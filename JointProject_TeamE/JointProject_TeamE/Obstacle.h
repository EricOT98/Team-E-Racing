/// <summary>
/// @Author: eric O' Toole
/// @version: 1.00
/// </summary>

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML\Graphics.hpp>
#include "ResourceManager.h"
enum class Type{BUSH,
				ROCK,
				BUMPER};
class Obstacle
{
public:
	Obstacle();
	~Obstacle();

	void initialise(sf::Vector2f pos, int type);
	void render(sf::RenderWindow & window);

protected:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::CircleShape m_boundingCircle;
	sf::Vector2f m_position;
	int m_rotation;
	bool m_alive;
	bool m_collided;
	Type m_type;
};
#endif;