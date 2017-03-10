#include "ResourceManager.h"

ResourceManager g_resourceMgr;

/// <summary>
/// Loads all required assets in game
/// </summary>
void ResourceManager::loadAssets(LevelData & levelIn)
{
	try
	{
<<<<<<< 255f19abf3899f7864c4edad5d504f35bb1a01c5
		textureHolder.acquire("CarTexture", thor::Resources::fromFile<sf::Texture>("Resources/TestRacer.png"));
		fontHolder.acquire("GameFont", thor::Resources::fromFile<sf::Font>("Resources/arial.ttf"));
=======
		holder.acquire("CarTexture", thor::Resources::fromFile<sf::Texture>("Car.png"));
		// -> Load more assets here etc
>>>>>>> Added a functional player that can be controlled on the screen

		std::string s;

		for (int i = 0; i < levelIn.m_textureDataVector.size(); i++)
		{
			s = levelIn.m_textureDataVector.at(i).m_filename;
			std::cout << s << levelIn.m_textureDataVector.size() << std::endl;
			textureHolder.acquire(levelIn.m_textureDataVector.at(i).m_textureName, thor::Resources::fromFile<sf::Texture>(levelIn.m_textureDataVector.at(i).m_filename));
		}
	}
	catch (thor::ResourceLoadingException& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}