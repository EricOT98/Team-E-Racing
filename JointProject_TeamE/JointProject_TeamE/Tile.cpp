#include "Tile.h"
#include <iostream>

Tile::Tile(int xIndex, int yIndex, std::string texture, int rotation) : m_xIndex(xIndex), m_yIndex(yIndex)
{
	//displayTexture.loadFromFile("sprite_2.png");
	m_displaySprite.setTexture(g_resourceMgr.holder[texture]);
	float spriteWidth = m_displaySprite.getLocalBounds().width;
	float spriteHeight = m_displaySprite.getLocalBounds().height;
	m_displaySprite.setPosition(spriteWidth * m_xIndex + spriteWidth / 2.f, spriteHeight * m_yIndex + spriteHeight / 2.f);
	m_displaySprite.setOrigin(m_displaySprite.getGlobalBounds().width / 2.f, m_displaySprite.getGlobalBounds().height / 2.f);
	m_displaySprite.setRotation(rotation);
}

sf::Sprite Tile::getSprite()
{
	return m_displaySprite;
}

int Tile::getIndexX()
{
	return m_xIndex;
}

int Tile::getIndexY()
{
	return m_yIndex;
}

void Tile::checkEdgeCollision()
{

}

void Tile::checkOnTrack()
{

}

void Tile::render(sf::RenderWindow & window)
{
	window.draw(m_displaySprite);
}