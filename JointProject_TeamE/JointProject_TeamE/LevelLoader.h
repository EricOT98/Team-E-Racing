#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "yaml-cpp\yaml.h"
#include <SFML\Graphics.hpp>
#include <iostream>

struct TextureData
{
	std::string m_filename;
	std::string m_textureName;
};

struct ObstacleData {
	std::string m_textureString;
	sf::Vector2f m_position;
	sf::IntRect m_textureRect;
	int m_type;
};

struct TileData {
	std::string m_textureString;
	int m_xIndex;
	int m_yIndex;
	int m_rotation;
};

struct PlayerData {
	sf::Vector2f position;
};

struct LevelData {
	PlayerData m_playerData;
	std::vector<TileData> m_tileDataVector;
	std::vector<TextureData> m_textureDataVector;
	std::vector<ObstacleData> m_obstacleDataVector;
};

class LevelLoader {
public:
	LevelLoader();
	static void load(LevelData & levelIn);
};

#endif
