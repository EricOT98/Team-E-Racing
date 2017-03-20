#ifndef TRACK_H
#define TRACK_H

#include <SFML\Graphics.hpp>
#include "Tile.h"
#include "Player.h"
#include "LevelLoader.h"
#include "ResourceManager.h"
#include "Obstacle.h"

enum class TrackType
{
	TrackOne = 0,
	TrackTwo,
	TrackThree,
	TrackFour
};

class Track {
public:
	Track();
	void setTrack(LevelData &levelIn);
	void update(std::vector<Racer *> & racers);
	void render(sf::RenderWindow & window);

private:
	bool checkRacerIntersection(Tile & tile, sf::Vector2f & racerPos);
	bool checkRacerObstacleCollision(OBB &playerOBB);
	bool checkWindowInterscetion(Tile & tile, sf::RenderWindow & window);
	bool checkWindowObsIntersection(Obstacle & obstacle, sf::RenderWindow & window);
	std::vector<Tile *> m_trackTiles;
	std::vector<Obstacle *> m_obstacles;

	sf::Sprite startPosSprite;
	std::vector<sf::Vector2f> m_startPositions;

	TrackType currentTrackType = TrackType::TrackThree;
};

#endif