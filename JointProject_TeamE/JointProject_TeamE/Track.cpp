#include "Track.h"

Track::Track() {  }

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
	startPosSprite.setOrigin(static_cast<int>(startPosSprite.getLocalBounds().width / 2.0f), static_cast<int>(startPosSprite.getLocalBounds().height / 2.0f));

	for (int i = 0; i < levelIn.m_startPositionData.size(); i++)
	{
		m_startPlayerPositions.push_back(levelIn.m_startPositionData.at(i).m_position);
	}

	playerStartPos = m_startPlayerPositions.at((int)TrackType::TrackOne);

	for (int i = 1; i <= numberOfAICars + 2; i++)
	{
		sf::Vector2f pos = sf::Vector2f(playerStartPos.x - ((i % 2) * 30), playerStartPos.y - (i * 45));
		m_startAIPositions.push_back(pos);
	}

	for (int i = 0; i < levelIn.m_checkpointData.size(); i++)
	{
		sf::RectangleShape rect(sf::Vector2f(levelIn.m_checkpointData.at(i).m_textureRect.width,
			levelIn.m_checkpointData.at(i).m_textureRect.height));
		rect.setPosition(sf::Vector2f(levelIn.m_checkpointData.at(i).m_textureRect.left,
			levelIn.m_checkpointData.at(i).m_textureRect.top));
		rect.setTexture(&g_resourceMgr.textureHolder[levelIn.m_checkpointData.at(i).m_texture]);
		rect.setOrigin(rect.getGlobalBounds().width / 2.f, rect.getGlobalBounds().height / 2.f);
		rect.setRotation(levelIn.m_checkpointData.at(i).m_rotation);
		CheckPointLine checkPoint;
		checkPoint.m_rect = rect;
		checkPoint.m_obb = OBB(rect.getPosition(), rect.getLocalBounds().width, rect.getLocalBounds().height, rect.getRotation());
		checkPoint.m_startLine = levelIn.m_checkpointData.at(i).m_start;
		m_checkPoints.push_back(checkPoint);
	}
}

void Track::update(std::vector<Racer *> & racers)
{
	for (auto & racer : racers)
	{
		for (auto & checkPoint : m_checkPoints)
		{
			if (checkRacerCheckPointIntersection(checkPoint.m_obb, racer->m_boundingBox))
			{
				racer->setCheckPoint(checkPoint.m_startLine);
			}
		}
		for (auto & tile : m_trackTiles)
		{
				if (checkRacerIntersection(*tile, racer->getPosition()))
				{
					tile->checkOnTrack(racer);
				}
		}

		if (checkRacerObstacleCollision(racer->m_boundingBox))
		{
			racer->resolveCollision();
		}

		//@Projectile
		for (auto & proj : racer->m_projectiles)
		{
			if (proj->getAlive())
			{
				for (auto & obs : m_obstacles)
				{
				if (proj->getElevation() < 0.5f)
				{
					if (checkProjectileObstacleCollision(proj->m_boundingBox)) {
					proj->despawn();
					break;
					}
				}
				}
				for (auto & checkedRacer : racers)
				{
					if (racer != checkedRacer)
					{
						if (checkProjectileRacerCollision(proj->m_boundingBox, checkedRacer->m_boundingBox))
						{
							proj->despawn();
							checkedRacer->resolveCollision();
							checkedRacer->setFrictionHigh();
						}
					}
				}
			}
		}
	}
}

std::vector<sf::Vector2f> *Track::getAIStartPositions()
{
	return &m_startAIPositions;
}

sf::Vector2f Track::getPlayerStartPosition()
{
	return playerStartPos;
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

	for (auto & check : m_checkPoints)
	{
		window.draw(check.m_rect);
		check.m_obb.debugRender(window);
	}

	for (int i = 0; i < numberOfAICars + 1; i++)
	{
		sf::Vector2f pos = sf::Vector2f(playerStartPos.x - ((i % 2) * 30), playerStartPos.y - (i * 45));
		startPosSprite.setPosition(pos);

		window.draw(startPosSprite);
	}
}

unsigned int Track::getNumOfAICars()
{
	return numberOfAICars;
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

bool Track::checkRacerObstacleCollision(OBB &playerOBB)
{
	for (Obstacle *obstacle : m_obstacles)
	{
		if (playerOBB.intersects(obstacle->m_obstacleOBB)
			&& obstacle->m_type == "Obstacle")
		{
			std::cout << "Collided with obstacle!" << std::endl;
			return true;
		}
	}

	return false;
}

bool Track::checkProjectileObstacleCollision(OBB & projectileOBB)
{
	for (Obstacle *obstacle : m_obstacles)
	{
		if (projectileOBB.intersects(obstacle->m_obstacleOBB))
		{
			std::cout << "Collision with Obstacle(Projectile)" << std::endl;
			return true;
		}
	}
	return false;
}

bool Track::checkProjectileRacerCollision(OBB &projectileOBB, OBB &racerOBB)
{

	if (projectileOBB.intersects(racerOBB))
	{
		std::cout << "Collision with car" << std::endl;
		return true;
	}
	return false;
}

bool Track::checkRacerCheckPointIntersection(OBB &checkPointOBB, OBB &racerOBB)
{
	if (checkPointOBB.intersects(racerOBB))
	{
		std::cout << "Checkpoint has been hit!" << std::endl;
		return true;
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