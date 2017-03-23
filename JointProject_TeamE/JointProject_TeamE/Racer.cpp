#include "Racer.h"

/// <summary>
/// Default constructor for a racer object
/// </summary>
Racer::Racer()
	: m_currentRotation(-90.0f)
{
	m_tireTexture.loadFromFile("Resources/Test.png");
	m_tireTracks.setTexture(m_tireTexture);
	m_index = m_tireTracks.addTextureRect(sf::IntRect(12, 0, 15, 5));
	m_trackEmmiter.setParticleTextureIndex(m_index);
	m_trackEmmiter.setParticlePosition(m_position);
	m_trackEmmiter.setParticleRotation(m_currentRotation);
	m_trackEmmiter.setParticleLifetime(sf::seconds(2));
	m_trackEmmiter.setParticleScale(sf::Vector2f(0.2f, 1.f));
	m_trackEmmiter.setEmissionRate(0);
	m_trackEmmiter2 = m_trackEmmiter;
	m_tireTracks.addEmitter(thor::refEmitter(m_trackEmmiter));
	m_tireTracks.addEmitter(thor::refEmitter(m_trackEmmiter2));
	thor::FadeAnimation fader(0.0f, 0.1f);
	m_tireTracks.addAffector(thor::AnimationAffector(fader));
	m_boundingBox = OBB(m_position, m_sprite.getLocalBounds().width * m_sprite.getScale().x,
		m_sprite.getLocalBounds().height * m_sprite.getScale().y, m_currentRotation);
	//@Projectile 
	numProjectiles = 10;
	for (int i = 0; i < numProjectiles; i++)
	{
		std::unique_ptr<Projectile> projectile(new Projectile());
		projectile->init("Bullet", "smoke");
		m_projectiles.push_back(std::move(projectile));
	}
	m_spotLight = SpotLight(m_position, sf::Vector2f(0.15f, 0.15f), sf::Color(255, 180, 130, 255));
	m_frictionHigh = 0.9f;
	m_frictionLow = 0.99f;
	m_currentFriction = m_frictionLow;
}

/// <summary>
/// Default destructor for a racer object
/// </summary>
Racer::~Racer() {}

/// <summary>
/// Render the racers car and name
/// </summary>
/// <param name="window"></param>
void Racer::render(sf::RenderWindow & window)
{
	//m_boundingBox.debugRender(window);
	window.draw(m_tireTracks);
	window.draw(m_sprite);

	sf::VertexArray line(sf::LinesStrip, 2);
	line[0].position = m_position;
	line[1].position = m_position + m_direction;
	window.draw(line);

	//@Projectile
	for (int i = 0; i < numProjectiles; i++)
	{
		if (m_projectiles.at(i)->getAlive()) {
			m_projectiles.at(i)->render(window);
		}
	}
}

/// <summary>
/// Sets the current car of the racer via pointer
/// </summary>
void Racer::setCar(CarData carData)
{ 
	m_sprite.setTexture(g_resourceMgr.textureHolder[carData.m_texture], true); // Set and resize the racer's texture
	m_sprite.setScale(sf::Vector2f(0.2f, 0.2f)); // Set the scale of the sprite
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getLocalBounds().width / 2.f, m_sprite.getLocalBounds().height / 2.f));
	m_sprite.setRotation(m_currentRotation);
	m_sprite.setPosition(m_position);
	m_acceleration = carData.m_acceleration;//250.f;
	m_deceleration = carData.m_deceleration;// 250.f;
	m_turnRate = carData.m_turnRate; // 150.f;
	// Set the acceleration, deceleration and turn rate for the racer
	m_acceleration = carData.m_acceleration;
	m_deceleration = carData.m_deceleration;
	m_turnRate = carData.m_turnRate;
	// Reset the lap tracking attributes
	m_lapsCompleted = 0;
	m_radius = 50.f;
	m_lastWayPointHit = false;
	m_spotLight.update(m_position + sf::Vector2f(40.0f * cos(degreesToRad(m_currentRotation)),
		40.0f * sin(degreesToRad(m_currentRotation))));
	m_currentNode = 0;
	m_currentRotation = -90.0f;
	m_velocity = 0;
	m_currentAcceleration = 0;
	m_lastWayPointHit = false;
	m_tireTracks.clearParticles();
}

/// <summary>
/// Sets the current position of the racer
/// </summary>
/// <param name="positonIn">The position the racer is to have</param>
void Racer::setPosition(sf::Vector2f positonIn)
{
	m_position = positonIn;
	m_sprite.setPosition(m_position);
}

/// <summary>
/// Simple getter function returns the Racers position
/// </summary>
/// <returns>Racer's position</returns>
sf::Vector2f Racer::getPosition()
{
	return m_position;
}

/// <summary>
/// Sets the current rotation of the racer
/// </summary>
/// <param name="rotationIn">The rotation the racer is to have</param>
void Racer::setRotation(float rotationIn)
{
	m_currentRotation = rotationIn;
	m_sprite.setRotation(m_currentRotation);
}

/// <summary>
/// Function determines what happens when a racer collides with an obstacle
/// </summary>
void Racer::resolveCollision()
{
	//m_velocity *= -1; // Invert the velocity
	//m_velocity -= 0.1f; // Subtract from the velocity
	//m_position = m_lastPosition; // Reset the position to a point where the racer was not in a collision situation
}

/// <summary>
/// Function calculates the movement of the racer and everything the racer has (eg: projectile)
/// </summary>
/// <param name="dt">delta time since the last update in milliseconds</param>
void Racer::calMovement(float dt)
{
	m_lastPosition = m_position; // Set the last position
	for (int i = 0; i < numProjectiles; i++)
	{
		m_projectiles.at(i)->update(dt); // Update all projectiles
	}
	m_sprite.setRotation(m_currentRotation);
	m_velocity += m_currentAcceleration * dt;
	m_direction = sf::Vector2f(std::cos(degreesToRad(m_currentRotation)), std::sin(degreesToRad(m_currentRotation)));
	unitVector(m_direction);
	float addOnTotal = m_velocity * dt + 0.5f * m_currentAcceleration * dt * dt; // formula: s = (ut) + (0.5 * at²)
	float xPosAddOn = addOnTotal * std::cos(degreesToRad(m_currentRotation));
	float yPosAddOn = addOnTotal * std::sin(degreesToRad(m_currentRotation));
	m_position.x += xPosAddOn;
	m_position.y += yPosAddOn;
	m_velocity *= m_currentFriction;
	m_sprite.setPosition(m_position);
	if ((m_velocity < 10.f && m_velocity > -10.f) && m_currentAcceleration == 0)
	{
		m_velocity = 0;
	}
	// Calculations forthe particle emission (skid marks)
	if (m_velocity > 0 && m_currentAcceleration < 0)
	{
		positionTracks();
		if (m_currentFriction == m_frictionLow)
		{
			m_trackEmmiter.setParticleColor(sf::Color::Black);
			m_trackEmmiter2.setParticleColor(sf::Color::Black);
		}
		else if(m_currentFriction == m_frictionHigh)
		{
			sf::Color col(100, 100, 20, 255);
			m_trackEmmiter.setParticleColor(col);
			m_trackEmmiter2.setParticleColor(col);
		}
	}
	else
	{
		m_trackEmmiter.setEmissionRate(0);
		m_trackEmmiter2.setEmissionRate(0);
	}


	m_currentAcceleration = 0; // Reset the acceleration
	m_tireTracks.update(m_clock.restart());

	// Check nodes for AI path following as well as lap tracking
	checkNodes();
}

void Racer::positionTracks()
{
	sf::Vector2f size = sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
	float radius = (((m_sprite.getGlobalBounds().width * 0.2f) / 2.0f) + (m_sprite.getGlobalBounds().height * 0.1f));
	float newX = m_position.x - (std::cos(thor::toRadian(m_currentRotation - 30)) * radius);
	float newY = m_position.y - (std::sin(thor::toRadian(m_currentRotation - 30)) * radius);
	
	m_trackEmmiter.setParticlePosition(sf::Vector2f(newX, newY));
	m_trackEmmiter.setParticleRotation(m_currentRotation + 90);
	newX = m_position.x - (std::cos(thor::toRadian(m_currentRotation + 30)) * radius);
	newY = m_position.y - (std::sin(thor::toRadian(m_currentRotation + 30)) * radius);
	m_trackEmmiter2.setParticlePosition(sf::Vector2f(newX, newY));
	m_trackEmmiter2.setParticleRotation(m_currentRotation + 90);

	m_trackEmmiter.setEmissionRate(60);
	m_trackEmmiter2.setEmissionRate(60);
}


/// <summary>
/// Function simply rotates the Racer left based on the 
/// percentage the analog stick has been moved and based 
/// off of time
/// </summary>
/// <param name="dt">delta time since last update</param>
/// <param name="percentageTurn">how much of a turn the player / AI wants (based off of the analog stick)</param>
void Racer::turnLeft(float dt, float percentageTurn)
{
	if (m_velocity > 5.f || m_velocity < -5.f) // Only turn while moving at a suitable speed
	{
		m_currentRotation -= m_turnRate * dt * (percentageTurn / 100); // Subtract from the current rotation
	}
}

/// <summary>
/// Function simply rotates the Racer right based on the 
/// percentage the analog stick has been moved and based 
/// off of time
/// </summary>
/// <param name="dt">delta time since last update</param>
/// <param name="percentageTurn">how much of a turn the player / AI wants (based off of the analog stick)</param>
void Racer::turnRight(float dt, float percentageTurn)
{
	if (m_velocity > 5.f || m_velocity < -5.f) // Only turn while moving at a suitable speed
	{
		m_currentRotation += m_turnRate * dt * (percentageTurn / 100); // Add to the current rotation
	}
}

/// <summary>
/// Function increases the racer's current acceleration based off of a percentage as well as delta time
/// </summary>
/// <param name="dt">delta time since last update</param>
/// <param name="percentageThrottle">percentage of the acceleration desired</param>
void Racer::accelerate(float dt, float percentageThrottle)
{
	m_currentAcceleration += m_acceleration * (percentageThrottle / 100); // 
}

/// <summary>
/// Function decreases the racer's current acceleration based off of a percentage as well as delta time
/// </summary>
/// <param name="dt">delta time since last update</param>
/// <param name="percentageBrake">percentage of the deceleration desired</param>
void Racer::decelerate(float dt, float percentageBrake)
{
	m_currentAcceleration -= m_deceleration * (percentageBrake / 100);
	
}

/// <summary>
/// Getter function simply returns the racer's rotation
/// </summary>
/// <returns>current rotation of the racer</returns>
float Racer::getRotation()
{
	return m_currentRotation;
}

/// <summary>
/// Function sets the friction for the racer to be high
/// </summary>
void Racer::setFrictionHigh()
{
	m_currentFriction = m_frictionHigh;
}

/// <summary>
/// Function sets the friction for the racer to be low
/// </summary>
void Racer::setFrictionLow()
{
	m_currentFriction = m_frictionLow;
}

/// <summary>
/// Function allows the racer to fire a projectile
/// </summary>
void Racer::fire()
{
	for (int i = 0; i < numProjectiles; i++)
	{
		if (!m_projectiles.at(i)->getAlive()) // We first check if we have a projectile that isn't currently alive
		{
			float totalRadius = (m_sprite.getGlobalBounds().height / 2.0f) + (m_projectiles.at(i)->getSize().y / 2.0f); // Check the radius of where the projectile can start from
			// Set the X and Y based off of the racer's rotation
			float newX = m_position.x + (totalRadius * std::cos(thor::toRadian(m_sprite.getRotation())));
			float newY = m_position.y + (totalRadius * std::sin(thor::toRadian(m_sprite.getRotation())));
			float power = 300; // Set up the power of the projectile
			if (m_velocity > 0)
			{
				power += m_velocity; // Alter the power based off of the velocity
			}
			m_projectiles.at(i)->spawnAt(sf::Vector2f(newX, newY), m_currentRotation, 10, power); // Set the spawn location of the projectile
			break; // Break out of the loop
		}
	}
}

/// <summary>
/// Function gets the total number of projectiles
/// </summary>
/// <returns>The number of projectiles</returns>
int Racer::getNumProjectiles()
{
	return numProjectiles;
}

/// <summary>
/// Function used to tell whether the racer has properly completed a lap of the track or not
/// </summary>
void Racer::setCheckPoint()
{
	if (m_lastWayPointHit)
	{
		m_lapsCompleted++; // Increment the laps completed if the player
		m_lastWayPointHit = false; // 
	}
}

/// <summary>
/// Function sets the pointer for the current waypoints of the racer
/// </summary>
/// <param name="wayPoints"></param>
void Racer::setWayPoints(std::vector<Waypoint> & wayPoints)
{
	m_wayPoints = &wayPoints;
}

/// <summary>
/// Function used to increment the current node number if the a node has been hit
/// </summary>
void Racer::checkNodes()
{
	if (distance(m_wayPoints->at(m_currentNode).m_position, m_position) < m_radius)
	{
		m_currentNode++; // Increment the current node if we have hit that node

		if (m_currentNode >= m_wayPoints->size())
		{
			m_currentNode = 0; // Reset the current node if the current node is the last node
			m_lastWayPointHit = true; // Set the last way point bool to be hit so a lap may be completed
		}
	}
}

/// <summary>
/// Function used to set the radius used to determine if a node has been hit
/// </summary>
/// <param name="radiusIn">The desired radius for node collision</param>
void Racer::setRadius(float radiusIn)
{
	m_radius = radiusIn;
}

/// <summary>
/// Getter function for the current lap the racer is on
/// </summary>
/// <returns>The amount of laps the racer has completed</returns>
int Racer::getLap()
{
	return m_lapsCompleted;
}