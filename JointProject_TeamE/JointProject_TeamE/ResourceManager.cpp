#include "ResourceManager.h"

ResourceManager g_resourceMgr;

/// <summary>
/// Loads all required assets in game
/// </summary>
void ResourceManager::loadAssets()
{
	holder.acquire("CarTexture", thor::Resources::fromFile<sf::Texture>("Resources/TestRacer.png"));
	// -> Load more assets here etc
}