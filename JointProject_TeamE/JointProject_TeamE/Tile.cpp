#include "Tile.h"
#include <iostream>

Tile::Tile(int xIndex, int yIndex, std::string texture, int rotation) 
	: m_xIndex(xIndex), m_yIndex(yIndex)
{
	m_displaySprite.setTexture(g_resourceMgr.textureHolder[texture]);
	// TODO(Darren): Don't load images again
	m_collisionImage.loadFromFile(texture + ".png");
	float spriteWidth = m_displaySprite.getLocalBounds().width;
	float spriteHeight = m_displaySprite.getLocalBounds().height;
	m_displaySprite.setPosition(spriteWidth * m_xIndex + spriteWidth / 2.f, spriteHeight * m_yIndex + spriteHeight / 2.f);
	m_displaySprite.setOrigin((int)(m_displaySprite.getGlobalBounds().width / 2.f), (int)(m_displaySprite.getGlobalBounds().height / 2.f));
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

void Tile::checkOnTrack(Racer * racer)
{
	sf::Vector2f relativePos = m_displaySprite.getPosition();
	relativePos.x -= m_displaySprite.getGlobalBounds().width / 2.f;
	relativePos.y -= m_displaySprite.getGlobalBounds().height / 2.f;
	relativePos = racer->getPosition() - relativePos;
	if (m_collisionImage.getPixel(relativePos.x, relativePos.y).r < 110)
	{
		racer->setFrictionLow();
	}
	else
	{
		racer->setFrictionHigh();
	}
}

void Tile::render(sf::RenderWindow & window)
{
	window.draw(m_displaySprite);
}