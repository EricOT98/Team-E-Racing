/// <summary>
/// @author: Eric O' Toole
/// @version: 1.0
/// </summary>
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Thor\Particles.hpp>
#include <Thor\Animations.hpp>
#include <SFML\Graphics.hpp>
#include "ResourceManager.h"
#include "..\MathUtility.h"

enum class ProjectileType {
	REGULAR,
	BOUNCE,
	TIMED
};
class Projectile
{
public:
	Projectile();
	~Projectile();

	void init(std::string texture);
	void update(float dt);
	void render(sf::RenderWindow & window);
	bool checkCollision(sf::Sprite & sprite);

	void cull();
	void despawn();
	void spawnAt(sf::Vector2f pos, float direction, int power);
	void setScale(sf::Vector2f scale);

	//Getter methods
	bool getAlive();
protected:
	void setPhysicsData();

	//Sprite data
	sf::Sprite m_sprite;
	sf::Vector2f m_scale;
	//Culling data
	bool m_alive;
	bool m_onScreen;
	bool m_collided;

	//Physics data
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	const int MAX_SPEED = 50.0f;
	int m_speed;
	float m_rotation;
	float m_width;
	float m_height;
	float m_radius;
	float m_radiusSqr;
};
#endif
