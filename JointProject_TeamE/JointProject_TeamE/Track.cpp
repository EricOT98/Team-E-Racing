#include "Track.h"

Track::Track() {}

void Track::setTrack(LevelData &levelIn)
{
	for (int i = 0; i < levelIn.m_tileDataVector.size(); i++)
	{
		m_trackTiles.push_back(new Tile(levelIn.m_tileDataVector.at(i).m_xIndex, levelIn.m_tileDataVector.at(i).m_yIndex, 
			levelIn.m_tileDataVector.at(i).m_textureString, levelIn.m_tileDataVector.at(i).m_rotation));
	}

	for (int i = 0; i < levelIn.m_obstacleDataVector.size(); i++)
	{
		m_obstacles.push_back(new Obstacle(levelIn.m_obstacleDataVector.at(i).m_textureString, levelIn.m_obstacleDataVector.at(i).m_textureRect, 
			levelIn.m_obstacleDataVector.at(i).m_position, levelIn.m_obstacleDataVector.at(i).m_type, levelIn.m_obstacleDataVector.at(i).m_rotation));
	}

	startPosSprite.setTexture(g_resourceMgr.textureHolder["StartTrackPos"]);
	startPosSprite.setScale(sf::Vector2f(0.2f, 0.2f));
	startPosSprite.setOrigin(startPosSprite.getLocalBounds().width / 2.0f, startPosSprite.getLocalBounds().height / 2.0f);

	for (int i = 0; i < levelIn.m_startPositionData.size(); i++)
	{
		m_startPositions.push_back(levelIn.m_startPositionData.at(i).m_position);
	}
}

void Track::update(std::vector<Racer *> & racers)
{
	for (auto & racer : racers)
	{
		for (auto & tile : m_trackTiles)
		{
			if (checkRacerIntersection(*tile, racer->getPosition()))
			{
				tile->checkOnTrack(racer);
			}
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

	// TODO(Darren): Move this into a set track method for the positions for current track
	//					so don't have to recalculate
	sf::Vector2f playerStartPos = m_startPositions.at((int)TrackType::TrackOne);
	for (int i = 0; i < 6; i++)
	{
		sf::Vector2f pos = sf::Vector2f(playerStartPos.x - ((i % 2) * 30), playerStartPos.y - (i * 40));
		startPosSprite.setPosition(pos);

		window.draw(startPosSprite);
	}
}

bool Track::checkRacerIntersection(Tile & tile, sf::Vector2f & racerPos)
{
	// Localise Values
	sf::Vector2f tilePos = tile.getSprite().getPosition();
	float tileWidth = tile.getSprite().getGlobalBounds().width / 2.f;
	float tileHeight = tile.getSprite().getGlobalBounds().height / 2.f;

	// Check for an intersection
	if (tilePos.x - tileWidth < racerPos.x && tilePos.x + tileWidth > racerPos.x)
	{
		if (tilePos.y - tileHeight < racerPos.y && tilePos.y + tileHeight > racerPos.y)
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

	if (tile.getSprite().getPosition().x - tile.getSprite().getGlobalBounds().width > viewRight)
	{
		return false;
	}
	else if (tile.getSprite().getPosition().y - tile.getSprite().getGlobalBounds().height > viewDown)
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