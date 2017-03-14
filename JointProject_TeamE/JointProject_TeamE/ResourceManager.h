/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef RESOURCE_MGR
#define RESOURCE_MGR

#include <Thor\Resources.hpp>
#include <SFML\Graphics.hpp>
#include "LevelLoader.h"
#include <iostream>

/// Handles all loading and retrieval of assets
/// 
/// Handles all loading and retrieval of assets using 
/// thor's library for asset loading and acquiring.
class ResourceManager
{
public:
	void loadAssets(LevelData & levelIn);
	thor::ResourceHolder<sf::Texture, std::string> textureHolder;
	thor::ResourceHolder<sf::Font, std::string> fontHolder;
	
};

extern ResourceManager g_resourceMgr;

#endif