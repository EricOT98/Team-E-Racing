#ifndef TILE_H
#define TILE_H

#include <SFML\Graphics.hpp>
#include "ResourceManager.h"
#include "Racer.h"
#include "MathUtility.h"

class Tile {
public:
	Tile(int xIndex, int yIndex, std::string texture, int rotation);
	void checkOnTrack(Racer * racer);
	void render(sf::RenderWindow & window);
	int getIndexX();
	int getIndexY();
	sf::Sprite getSprite();

private:
	sf::Sprite m_displaySprite;
	sf::Image m_collisionImage;
	int m_xIndex;
	int m_yIndex;
};

#endif
