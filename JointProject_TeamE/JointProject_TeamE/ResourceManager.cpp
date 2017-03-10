#include "ResourceManager.h"

ResourceManager g_resourceMgr;

/// <summary>
/// Loads all required assets in game
/// </summary>
void ResourceManager::loadAssets()
{
	try
	{
		holder.acquire("CarTexture", thor::Resources::fromFile<sf::Texture>("Resources/TestRacer.png"));
		holder.acquire("Obstacles", thor::Resources::fromFile<sf::Texture>("Resources/objects.png"));
		// -> Load more assets here etc
	}
	catch (thor::ResourceLoadingException& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}