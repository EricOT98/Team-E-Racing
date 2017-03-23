#ifndef TRACK_H
#define TRACK_H

#include <SFML\Graphics.hpp>
#include "Tile.h"
#include "Player.h"
#include "LevelLoader.h"
#include "ResourceManager.h"
#include "Obstacle.h"
#include "SpotLight.h"

struct CheckPointLine {
	bool m_startLine;
	sf::RectangleShape m_rect;
	OBB m_obb;
};

class Track 
{
public:
	Track();
	void setTrack(LevelData &levelIn, int trackIndex);
	void update(std::vector<Racer *> & racers);
	void render(sf::RenderWindow & window);
	std::vector<sf::Vector2f> *getAIStartPositions();
	sf::Vector2f getPlayerStartPosition();
	unsigned int getNumOfAICars();

private:
	bool checkRacerIntersection(Tile & tile, sf::Vector2f & racerPos);
	bool checkRacerObstacleCollision(OBB &playerOBB);
	bool checkProjectileObstacleCollision(OBB &projectileOBB);
	bool checkWindowInterscetion(Tile & tile, sf::RenderWindow & window);
	bool checkWindowObsIntersection(Obstacle & obstacle, sf::RenderWindow & window);

	//-------------------------------
	bool checkOBBIntersection(OBB & obb1, OBB & obb2);
	//-------------------------------

	std::vector<Tile *> m_trackTiles;
	std::vector<Obstacle *> m_obstacles;

	sf::Sprite startPosSprite;
	std::vector<sf::Vector2f> m_startPlayerPositions;
	std::vector<sf::Vector2f> m_startAIPositions;

	std::vector<CheckPointLine> m_checkPoints;
	sf::Vector2f playerStartPos;
	unsigned int numberOfAICars = 5;
};

#endif