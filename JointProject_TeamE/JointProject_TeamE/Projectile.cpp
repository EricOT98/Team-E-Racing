#include "Projectile.h"

/// <summary>
/// Basic projectile construtor for properties initialisation
/// </summary>
Projectile::Projectile()
{
	MAX_SPEED = 500;
	m_rotation = 0;
	m_position = sf::Vector2f(0, 0);
	m_velocity = sf::Vector3f(0, 0, GRAVITY);
	m_scale = sf::Vector2f(1.0f, 1.0f);
	m_width = 0;
	m_height = 0;
}

/// <summary>
/// Basic projectile destructor
/// </summary>
Projectile::~Projectile()
{
}

void Projectile::init(std::string texture)
{
	m_sprite.setTexture(g_resourceMgr.textureHolder[texture]);
	m_sprite.setTextureRect(sf::IntRect(12, 26, 10, 25));
	m_sprite.setOrigin(static_cast<int>(m_sprite.getLocalBounds().width / 2.0f), static_cast<int>(m_sprite.getLocalBounds().height / 2.0f));
	setScale(sf::Vector2f(0.3f, 0.3f));
	m_alive = false;
	m_onScreen = false;
	m_collided = false;
	setPhysicsData();
	m_boundingBox = OBB(m_position, m_sprite.getLocalBounds().width * m_sprite.getScale().x,
		m_sprite.getLocalBounds().height * m_sprite.getScale().y, m_rotation);
}

/// <summary>
/// This method is used to move the projectile in it's given direction.
/// </summary>
/// <param name="dt">Time taken in milliseconds since last update</param>
void Projectile::update(float dt)
{
	if (m_alive)
	{
		m_sprite.setRotation(m_rotation + 90);
		float addOnTotal = m_speed * dt + 0.5f * dt * dt; // formula: s = (ut) + (0.5 * at²)
		float xPosAddOn = addOnTotal * std::cos(degreesToRad(m_rotation));
		float yPosAddOn = addOnTotal * std::sin(degreesToRad(m_rotation));
		m_position.x += xPosAddOn;
		m_position.y += yPosAddOn;
		m_sprite.setPosition(m_position);
		m_boundingBox.construct(m_position, sf::Vector2f(m_sprite.getLocalBounds().width * m_sprite.getScale().x,
			m_sprite.getLocalBounds().height * m_sprite.getScale().y), m_sprite.getRotation());
		if (m_onScreen){

		}
	}
}

/// <summary>
/// This method renders the sprite and all effects only
/// if the sprite is on screen
/// </summary>
/// <param name="window"></param>
void Projectile::render(sf::RenderWindow & window)
{
	if (m_onScreen){
		m_boundingBox.debugRender(window);
		window.draw(m_sprite);
	}
}

/// <summary>
/// This method is used to check for a collisin between the Projectile and any
/// sprite. This method using Circular collision first to quickly calculate any
/// chance of a collision. If a collision is possible the method then uses "Pixel
/// Perfect" collision detection algorithims to determine if the sprites do collide
/// The method then returns if a collision has happened or not
/// </summary>
/// <param name="sprite">The sprite the Projectile is checking collisions against</param>
/// <returns></returns>
bool Projectile::checkCollision(sf::Sprite & sprite)
{
	sf::Vector2f spritePos = sprite.getPosition();
	//(x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) < (r1 + r2) * (r1 + r2)
	float tempRadiusSqr = 0;
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	if (spriteBounds.width < spriteBounds.height){
		tempRadiusSqr = spriteBounds.height * spriteBounds.height;
	}
	else {
		tempRadiusSqr = spriteBounds.width * spriteBounds.width;
	}
	if (distance(spritePos, m_position) < m_radiusSqr + tempRadiusSqr)
	{
		std::cout << "Collision: " << m_position.x << " " << m_position.y << std::endl;
		return true;
	}
	else {
		return false;
	}
}

/// <summary>
/// This method is used to tell the projectile it is off screen and hence
/// the projectile will no longer need to be drawn
/// </summary>
void Projectile::cull()
{
	m_onScreen = false;
}

/// <summary>
/// This method is used to despawn a projectile
/// </summary>
void Projectile::despawn()
{
	m_alive = false;
	m_onScreen = false;
}

/// <summary>
/// This method is used to spawn any projectile at a given point with
/// a given rotation and speed.
/// </summary>
/// <param name="pos"></param>
/// <param name="direction"></param>
/// <param name="power"></param>
void Projectile::spawnAt(sf::Vector2f pos, float direction,float pitch, int power)
{
	m_position = pos;
	m_rotation = direction;
	m_pitch = pitch;
	if (power < MAX_SPEED){
		m_speed = power;
	}
	else {
		m_speed = MAX_SPEED;
	}
	m_velocity = sf::Vector3f(std::cos(m_rotation) * std::cos(m_pitch) * power, std::sin(m_rotation) * std::sin(m_pitch) * power, std::sin(m_pitch) * m_speed);
	m_alive = true;
	m_onScreen = true;
}

/// <summary>
/// Set the scale of the projectile sprite
/// </summary>
/// <param name="scale">Scale of the projectile sprite</param>
void Projectile::setScale(sf::Vector2f scale)
{
	m_scale = scale;
	m_sprite.setScale(scale);
	setPhysicsData();
}

bool Projectile::getAlive()
{
	return m_alive;
}

sf::Vector2f Projectile::getSize()
{
	return sf::Vector2f(m_width, m_height);
}

/// <summary>
/// This method is used to initialise and recreate the data needed for collision detctions
/// for the projectile.
/// </summary>
void Projectile::setPhysicsData()
{
	m_width = m_sprite.getGlobalBounds().width;
	m_height = m_sprite.getGlobalBounds().height;
	if (m_width < m_height){
		m_radius = m_width;
	}
	else{
		m_radius = m_height;
	}
	m_radiusSqr = m_radius * m_radius;
}
