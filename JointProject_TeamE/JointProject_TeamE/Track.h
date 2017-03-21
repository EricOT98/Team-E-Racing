#ifndef TRACK_H
#define TRACK_H

#include <SFML\Graphics.hpp>
#include "Tile.h"
#include "Player.h"
#include "LevelLoader.h"
#include "ResourceManager.h"
#include "Obstacle.h"
#include "SpotLight.h"

enum class TrackType
{
	TrackOne = 0,
	TrackTwo,
	TrackThree,
	TrackFour
};

class Track 
{
public:
	Track();
	void setTrack(LevelData &levelIn);
	void update(std::vector<Racer *> & racers);
	void render(sf::RenderWindow & window);
	std::vector<sf::Vector2f> *getAIStartPositions();
	sf::Vector2f getPlayerStartPosition();
	unsigned int getNumOfAICars();

private:
	bool checkRacerIntersection(Tile & tile, sf::Vector2f & racerPos);
	bool checkRacerObstacleCollision(OBB &playerOBB);
	bool checkProjectileObstacleCollision(OBB &projectileOBB);
	bool checkProjectileRacerCollision(OBB &projectileOBB, OBB &racerOBB);
	bool checkWindowInterscetion(Tile & tile, sf::RenderWindow & window);
	bool checkWindowObsIntersection(Obstacle & obstacle, sf::RenderWindow & window);
	std::vector<Tile *> m_trackTiles;
	std::vector<Obstacle *> m_obstacles;

	sf::Sprite startPosSprite;
	std::vector<sf::Vector2f> m_startPlayerPositions;
	std::vector<sf::Vector2f> m_startAIPositions;
	sf::Vector2f playerStartPos;
	unsigned int numberOfAICars = 5;

	TrackType currentTrackType = TrackType::TrackThree;
	bool collision;
	sf::Clock m_countdownClock;
	float m_timer; float m_time;
};

#endif