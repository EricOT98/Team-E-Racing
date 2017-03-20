#include "Racer.h"

/// <summary>
/// Default constructor for a racer object
/// </summary>
Racer::Racer()
{

}

/// <summary>
/// Default destructor for a racer object
/// </summary>
Racer::~Racer()
{
}

/// <summary>
/// Render the racers car and name
/// </summary>
/// <param name="window"></param>
void Racer::render(sf::RenderWindow & window)
{
	//m_boundingBox.debugRender(window);
	window.draw(m_tireTracks);
	window.draw(m_sprite);
	//@Projectile
	if (m_test.getAlive()) {
		m_test.render(window);
	}
}

/// <summary>
/// Sets the current car of the racer via pointer
/// </summary>
void Racer::setCar()
{
	m_position.x = 300.f;
	m_position.y = 300.f;
	m_sprite.setTexture(g_resourceMgr.textureHolder["CarTexture"]);
	m_sprite.setScale(sf::Vector2f(0.2f, 0.2f));
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getLocalBounds().width / 2.f, m_sprite.getLocalBounds().height / 2.f));
	m_acceleration = 250.f;
	m_deceleration = 250.f;
	m_turnRate = 150.f;
	m_frictionHigh = 0.9f;
	m_frictionLow = 0.99f;
	m_currentFriction = m_frictionLow;
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
	m_test.init("Bullet");
}

/// <summary>
/// Sets the current position of the racer
/// </summary>
/// <param name="positonIn">The position the racer is to have</param>
void Racer::setPosition(sf::Vector2f positonIn)
{
	m_position = positonIn;
}

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
}

void Racer::resolveCollision()
{
	
}

void Racer::calMovement(float dt)
{
	//@Projectile
	m_test.update(dt);
	m_sprite.setRotation(m_currentRotation);
	m_velocity += m_currentAcceleration * dt;
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
	if (m_velocity > 0 && m_currentAcceleration < 0)
	{
		float newX = m_position.x - (std::cos(thor::toRadian(m_currentRotation - 30)) * (((m_sprite.getGlobalBounds().width * 0.2f) / 2.0f) + (m_sprite.getGlobalBounds().height * 0.1f)));
		float newY = m_position.y - (std::sin(thor::toRadian(m_currentRotation - 30)) * (((m_sprite.getGlobalBounds().width * 0.2f) / 2.0f) + (m_sprite.getGlobalBounds().height * 0.1f)));
		m_trackEmmiter.setEmissionRate(60);
		m_trackEmmiter.setParticlePosition(sf::Vector2f(newX, newY));
		m_trackEmmiter.setParticleRotation(m_currentRotation + 90);
		newX = m_position.x - (std::cos(thor::toRadian(m_currentRotation + 30)) * (((m_sprite.getGlobalBounds().width * 0.2f) / 2.0f) + (m_sprite.getGlobalBounds().height * 0.1f)));
		newY = m_position.y - (std::sin(thor::toRadian(m_currentRotation + 30)) * (((m_sprite.getGlobalBounds().width * 0.2f) / 2.0f) + (m_sprite.getGlobalBounds().height * 0.1f)));
		m_trackEmmiter2.setEmissionRate(60);
		m_trackEmmiter2.setParticlePosition(sf::Vector2f(newX, newY));
		m_trackEmmiter2.setParticleRotation(m_currentRotation + 90 );

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


	m_currentAcceleration = 0;
	m_tireTracks.update(m_clock.restart());
}

void Racer::turnLeft(float dt, float percentageTurn)
{
	if (m_velocity > 5.f || m_velocity < -5.f)
	{
		m_currentRotation -= m_turnRate * dt * (percentageTurn / 100);
	}
}

void Racer::turnRight(float dt, float percentageTurn)
{
	if (m_velocity > 5.f || m_velocity < -5.f)
	{
		m_currentRotation += m_turnRate * dt * (percentageTurn / 100);
	}
}

void Racer::accelerate(float dt, float percentageThrottle)
{
	m_currentAcceleration += m_acceleration * (percentageThrottle / 100);
}

void Racer::decelerate(float dt, float percentageBrake)
{
	m_currentAcceleration -= m_deceleration * (percentageBrake / 100);
	
}

float Racer::getRotation()
{
	return m_currentRotation;
}

void Racer::setFrictionHigh()
{
	m_currentFriction = m_frictionHigh;
}

void Racer::setFrictionLow()
{
	m_currentFriction = m_frictionLow;
}

void Racer::fire()
{
	float totRadius = (m_sprite.getGlobalBounds().height / 2.0f) + (m_test.getSize().y / 2.0f);
	float newX = m_position.x + (totRadius * std::cos(thor::toRadian(m_sprite.getRotation())));
	float newY = m_position.y + (totRadius * std::sin(thor::toRadian(m_sprite.getRotation())));
	float power = 300;
	if (m_velocity > 0)
	{
		power += m_velocity;
	}
	m_test.spawnAt(sf::Vector2f(newX, newY), m_currentRotation,10, power);
}
//
//Projectile* Racer::getProjectile()
//{
//	if (m_test.getAlive())
//	{
//		return &m_test;
//	}
//	else {
//		return nullptr;
//	}
//}
