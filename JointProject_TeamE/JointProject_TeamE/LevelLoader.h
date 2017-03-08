#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "yaml-cpp\yaml.h"
#include <SFML\Graphics.hpp>
#include <iostream>

struct PlayerData {
	sf::Vector2f position;
};

struct LevelData {
	PlayerData m_playerData;
};

class LevelLoader {
public:
	LevelLoader();
	static void load(LevelData & levelIn);
};

#endif
