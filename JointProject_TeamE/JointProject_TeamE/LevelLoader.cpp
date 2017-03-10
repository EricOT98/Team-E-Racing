#include "LevelLoader.h"
#include <iostream>

void operator >> (const YAML::Node &textureNode, TextureData &texture)
{
	texture.m_filename = textureNode["filepath"].as<std::string>();
	texture.m_textureName = textureNode["string"].as<std::string>();
	std::cout << texture.m_filename << " - " << texture.m_textureName << std::endl;
}

void operator >> (const YAML::Node &tileNode, TileData & tile)
{
	tile.m_textureString = tileNode["texturestring"].as<std::string>();
	tile.m_xIndex = tileNode["index"]["x"].as<int>();
	tile.m_yIndex = tileNode["index"]["y"].as<int>();
	tile.m_rotation = tileNode["rotation"].as<int>();
}

void operator >> (YAML::Node &playerNode, PlayerData & player)
{
	player.position.x = playerNode["x"].as<float>();
	player.position.y = playerNode["y"].as<float>();
}

void operator >> (YAML::Node &baseNode, LevelData &levelIn)
{
	baseNode["player"] >> levelIn.m_playerData;
	const YAML::Node& tileNode = baseNode["tiles"].as<YAML::Node>();
	for (unsigned int i = 0; i < tileNode.size(); ++i)
	{
		TileData tile;
		tileNode[i] >> tile;
		levelIn.m_tileDataVector.push_back(tile);
	}

	const YAML::Node& textureNode = baseNode["textures"].as<YAML::Node>();
	for (unsigned int i = 0; i < textureNode.size(); ++i)
	{
		TextureData texture;
		textureNode[i] >> texture;
		levelIn.m_textureDataVector.push_back(texture);
	}
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