#include "Track.h"

Track::Track() {}

void Track::setTrack(LevelData levelIn)
{
	for (int i = 0; i < 16; i++)
	{
		m_trackTiles.push_back(new Tile(levelIn.m_tileDataVector.at(i).m_xIndex, levelIn.m_tileDataVector.at(i).m_yIndex, levelIn.m_tileDataVector.at(i).m_textureString, levelIn.m_tileDataVector.at(i).m_rotation));
	}
	for (int i = 0; i < 4; i++)
	{
		m_obstacles.push_back(new Obstacle(levelIn.m_obstacleDataVector.at(i).m_textureString, levelIn.m_obstacleDataVector.at(i).m_textureRect, levelIn.m_obstacleDataVector.at(i).m_position, levelIn.m_obstacleDataVector.at(i).m_type));
	}
}

void Track::update(std::vector<Racer> & racers)
{
	for (auto & racer : racers)
	{
		for (auto & tile : m_trackTiles)
		{
			//if (checkRacerIntersection(tile, racer.getPosition())) // Needs a racer getPosition method
			//{

			//}
		}
	}
}

void Track::render(sf::RenderWindow & window)
{
	for (int i = 0; i < m_trackTiles.size(); i++)
	{
		int j = m_trackTiles.size();
		if (checkWindowInterscetion(*m_trackTiles.at(i), window))
		{
			m_trackTiles.at(i)->render(window);
		}
	}
	for (int i = 0; i < m_obstacles.size(); i++)
	{
		int j = m_obstacles.size();
		if (checkWindowObsIntersection(*m_obstacles.at(i), window))
		{
			m_obstacles.at(i)->render(window);
		}
	}
}

bool Track::checkRacerIntersection(Tile & tile, sf::Vector2f & racerPos)
{
	// Localise Values
	sf::Vector2f tilePos = tile.getSprite().getPosition();
	float tileWidth = tile.getSprite().getGlobalBounds().width;
	float tileHeight = tile.getSprite().getGlobalBounds().height;

	// Check for an intersection
	if (tilePos.x < racerPos.x && tilePos.x + tileWidth > racerPos.x)
	{
		if (tilePos.y < racerPos.y && tilePos.y + tileHeight > racerPos.y)
		{
			return true;
		}
	}
	return false;
}

bool Track::checkWindowInterscetion(Tile & tile, sf::RenderWindow & window)
{
	float viewLeft = window.getView().getCenter().x - window.getSize().x / 2.f;
	float viewRight = window.getView().getCenter().x + window.getSize().x / 2.f;
	float viewUp = window.getView().getCenter().y - window.getSize().y / 2.f;
	float viewDown = window.getView().getCenter().y + window.getSize().y / 2.f;

	if (tile.getSprite().getPosition().x > viewRight)
	{
		return false;
	}
	else if (tile.getSprite().getPosition().y > viewDown)
	{
		return false;
	}
	else if (tile.getSprite().getPosition().x + tile.getSprite().getGlobalBounds().width < viewLeft)
	{
		return false;
	}
	else if (tile.getSprite().getPosition().y + tile.getSprite().getGlobalBounds().height < viewUp)
	{
		return false;
	}
	return true;
}

bool Track::checkWindowObsIntersection(Obstacle & obstacle, sf::RenderWindow & window)
{
	float viewLeft = window.getView().getCenter().x - window.getSize().x / 2.f;
	float viewRight = window.getView().getCenter().x + window.getSize().x / 2.f;
	float viewUp = window.getView().getCenter().y - window.getSize().y / 2.f;
	float viewDown = window.getView().getCenter().y + window.getSize().y / 2.f;

	if (obstacle.getSprite().getPosition().x > viewRight)
	{
		return false;
	}
	else if (obstacle.getSprite().getPosition().y > viewDown)
	{
		return false;
	}
	else if (obstacle.getSprite().getPosition().x + obstacle.getSprite().getGlobalBounds().width < viewLeft)
	{
		return false;
	}
	else if (obstacle.getSprite().getPosition().y + obstacle.getSprite().getGlobalBounds().height < viewUp)
	{
		return false;
	}
	return true;
}
