#ifndef TRACK_H
#define TRACK_H

#include <SFML\Graphics.hpp>
#include "Tile.h"
#include "Player.h"
#include "LevelLoader.h"
#include "ResourceManager.h"
#include "Obstacle.h"

class Track {
public:
	Track();
	void setTrack(LevelData levelIn);
	void update(std::vector<Racer *> & racers);
	void render(sf::RenderWindow & window);
private:
	bool checkRacerIntersection(Tile & tile, sf::Vector2f & racerPos);
	bool checkWindowInterscetion(Tile & tile, sf::RenderWindow & window);
	bool checkWindowObsIntersection(Obstacle & obstacle, sf::RenderWindow & window);
	std::vector<Tile *> m_trackTiles;
	std::vector<Obstacle *> m_obstacles;
};

#endif