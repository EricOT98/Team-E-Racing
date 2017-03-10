#include "Obstacle.h"

/// <summary>
/// Simple obstacle constructor to load in the varying obstacle sprites and textures
/// </summary>
/// <param name="pos">The position of the obstacle</param>
/// <param name="type">the type of obstacle it is</param>
Obstacle::Obstacle()
{
}

/// <summary>
/// Obstacle destructor
/// </summary>
Obstacle::~Obstacle()
{
}

/// <summary>
/// initialise all elements for the obstacle
/// </summary>
void Obstacle::initialise(sf::Vector2f pos, int type)
{
	m_texture = g_resourceMgr.holder["Obstacles"];
	m_sprite.setTexture(m_texture);
	switch (type)
	{
	case 0:
		m_sprite.setTextureRect(sf::IntRect(585, 345, 50, 50));
		m_type = Type::BUMPER;
		break;
	case 1:
		m_sprite.setTextureRect(sf::IntRect(265, 320, 55, 50));
		m_type = Type::ROCK;
		break;
	case 2:
		m_sprite.setTextureRect(sf::IntRect(635, 420, 45, 40));
		m_type = Type::BUSH;
		break;
	default:
		m_sprite.setTextureRect(sf::IntRect(265, 320, 55, 50));
		m_type = Type::ROCK;
		break;
	}
}

/// <summary>
/// Draw the obstacle
/// </summary>
/// <param name="window"></param>
void Obstacle::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}
