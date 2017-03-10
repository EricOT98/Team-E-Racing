#ifndef TILE_H
#define TILE_H

#include <SFML\Graphics.hpp>
#include "ResourceManager.h"

class Tile {
public:
	Tile(int xIndex, int yIndex, std::string texture, int rotation);
	void checkOnTrack();
	void checkEdgeCollision();
	void render(sf::RenderWindow & window);
	int getIndexX();
	int getIndexY();
	sf::Sprite getSprite();

	// Temporary methods
	sf::Texture displayTexture;
	// End temp methods

private:
	sf::Sprite m_displaySprite;
	sf::Image m_collisionImage;
	int m_xIndex;
	int m_yIndex;
};

#endif
