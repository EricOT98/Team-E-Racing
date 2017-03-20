#include "Projectile.h"

/// <summary>
/// Basic projectile construtor for properties initialisation
/// </summary>
Projectile::Projectile()
{
	MAX_SPEED = 500;
	m_rotation = 0;
	m_position = sf::Vector2f(0, 0);
	m_gravity = -9.8f * 10.f;
	m_velocity = sf::Vector3f(0, 0, 0);
	m_scale = sf::Vector2f(1.0f, 1.0f);
	m_width = 0;
	m_height = 0;
	m_exploded = false;
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
	m_smokeTrail.setTexture(g_resourceMgr.textureHolder[texture]);
	m_trailEmmiter.setEmissionRate(30);
	m_trailEmmiter.setParticleLifetime(sf::seconds(.5f));
	m_trailEmmiter.setParticleScale(sf::Vector2f(0.1f, 0.1f));
	m_smokeTrail.addEmitter(thor::refEmitter(m_trailEmmiter));


	//m_explosionTexture.loadFromFile("Resources/Projectiles/Explosion.png");
	//float animationStepX = m_explosionTexture.getSize().x / 8.0f;
	//float animationStepY = m_explosionTexture.getSize().y / 8.0f;
	//int x = 0, y = 0;
	//float frameTime = 0;
	//frameTime = 1 / 64.0f;
	//int frameIndex = 0;
	//for (int i = 0; i < m_explosionTexture.getSize().x; i+= animationStepX)
	//{
	//	for (int j = 0; j < m_explosionTexture.getSize().y; j += animationStepY)
	//	{
	//		sf::IntRect rect(x * i, y*i, animationStepX, animationStepY);
	//		m_explosion.addFrame(0.5f, rect);
	//	}
	//}
	//m_explosionSprite.setTexture(m_explosionTexture);
	//m_explosionSprite.setTextureRect(sf::IntRect(0,0, animationStepX, animationStepY));
	//m_explosion(m_explosionSprite, m_animationProgress);
	//m_explosionAnimator.addAnimation("explode", m_explosion, sf::seconds(5.0f));
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

		m_velocity = m_velocity + sf::Vector3f(0, 0, m_gravity * dt);
		//s = ut + 1/2atsqr
		m_elevation = (m_velocity.z * dt) + 0.5f * m_gravity * (dt * dt);
		m_scale.x = (m_elevation / 2.0f);
		m_scale.y = (m_elevation / 2.0f);
		setScale(m_scale);
		//@Debug
		//std::cout << "z = " << m_elevation << std::endl;
		if (m_elevation < 0)
		{
			despawn();
		}
		m_boundingBox.construct(m_position, sf::Vector2f(m_sprite.getLocalBounds().width * m_sprite.getScale().x,
			m_sprite.getLocalBounds().height * m_sprite.getScale().y), m_sprite.getRotation());
		if (m_onScreen){
			m_trailEmmiter.setEmissionRate(30);
			m_trailEmmiter.setParticlePosition(m_position);
		}
		else {
			m_trailEmmiter.setEmissionRate(0);
		}
		m_smokeTrail.update(m_clock.restart());
	}
	//m_explosionAnimator.update(m_clock.restart());
	//m_explosionAnimator.animate(m_explosionSprite);
	//std::cout << "Pos: " << m_explosionSprite.getPosition().x << " " << m_explosionSprite.getPosition().y << std::endl;
	///*if (!m_explosionAnimator.isPlayingAnimation())
	//{
	//	m_exploded = false;
	//}*/
	//m_explosionSprite.setPosition(m_explosionPos);
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
		window.draw(m_smokeTrail);
		window.draw(m_sprite);
	}
	//std::cout << "rendering explosion" << std::endl;
	//window.draw(m_explosionSprite);
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
	m_exploded = true;
	//m_explosionAnimator.stopAnimation();
	//m_explosionAnimator.playAnimation("explode", false);
	//m_explosionAnimator.animate(m_explosionSprite);
	//m_explosionPos = m_sprite.getPosition();
	//m_sprite.setPosition(m_position);
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
	m_velocity = sf::Vector3f(std::cos(degreesToRad(m_rotation)) * std::cos(degreesToRad(m_pitch)) * power, std::sin(degreesToRad(m_rotation)) * std::sin(degreesToRad(m_pitch)) * power, std::sin(degreesToRad(m_pitch)) * m_speed);
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

float Projectile::getElevation()
{
	return m_elevation;
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
