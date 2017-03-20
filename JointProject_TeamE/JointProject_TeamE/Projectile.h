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
#include "OBB.h"

//Constants
const float GRAVITY = 9.8f;

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

	OBB m_boundingBox;

	void init(std::string texture);
	void update(float dt);
	void render(sf::RenderWindow & window);
	bool checkCollision(sf::Sprite & sprite);

	void cull();
	void despawn();
	void spawnAt(sf::Vector2f pos, float direction, float pitch, int power);
	void setScale(sf::Vector2f scale);

	//Getter methods
	bool getAlive();
	sf::Vector2f getSize();
protected:
	void setPhysicsData();
	void applyVerticalImpulse();
	//Sprite data
	sf::Sprite m_sprite;
	sf::Vector2f m_scale;
	//Culling data
	bool m_alive;
	bool m_onScreen;
	bool m_collided;

	//Physics data
	sf::Vector2f m_position;
	sf::Vector3f m_velocity;
	int MAX_SPEED;
	int m_speed;
	float m_rotation;
	float m_pitch;
	float m_width;
	float m_height;
	float m_radius;
	float m_radiusSqr;

	
};
#endif
