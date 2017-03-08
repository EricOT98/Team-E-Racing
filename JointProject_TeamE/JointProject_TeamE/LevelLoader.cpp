#include "LevelLoader.h"

void operator >> (YAML::Node &playerNode, PlayerData & player)
{
	player.position.x = playerNode["x"].as<float>();
	player.position.y = playerNode["y"].as<float>();
}

void operator >> (YAML::Node &baseNode, LevelData &levelIn)
{
	baseNode["player"] >> levelIn.m_playerData;
}

LevelLoader::LevelLoader() {}

void LevelLoader::load(LevelData & levelIn)
{
	try 
	{
		YAML::Node baseNode = YAML::LoadFile("Track.yaml");
		if (baseNode.IsNull())
		{
			throw std::exception("Error: File Not Found!");
		}
		else
		{
			baseNode >> levelIn;
		}
	}
	catch (YAML::ParserException& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Error: Unknown Cause!" << std::endl;
	}
}