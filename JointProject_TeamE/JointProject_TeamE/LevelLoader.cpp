#include "LevelLoader.h"
#include <iostream>

void operator >> (const YAML::Node &textureNode, TextureData &texture)
{
	texture.m_filename = textureNode["filepath"].as<std::string>();
	texture.m_textureName = textureNode["string"].as<std::string>();
	std::cout << texture.m_filename << " - " << texture.m_textureName << std::endl;
}

/// <summary>
/// Overloaded operator to allow loading of obstacles
/// </summary>
/// <param name="obstacleNode"> The obstacle node in YAML file</param>
/// <param name="obstacle">Obstacle object created to push back to the vector</param>
void operator >> (const YAML::Node &obstacleNode, ObstacleData & obstacle)
{
	obstacle.m_textureString = obstacleNode["texturestring"].as<std::string>();
	obstacle.m_type = obstacleNode["type"].as<std::string>();
	obstacle.m_position.x = obstacleNode["position"]["x"].as<float>();
	obstacle.m_position.y = obstacleNode["position"]["y"].as<float>();
	obstacle.m_textureRect.left = obstacleNode["texturerect"]["left"].as<int>();
	obstacle.m_textureRect.top = obstacleNode["texturerect"]["top"].as<int>();
	obstacle.m_textureRect.width = obstacleNode["texturerect"]["width"].as<int>();
	obstacle.m_textureRect.height = obstacleNode["texturerect"]["height"].as<int>();
	obstacle.m_name = obstacleNode["name"].as<std::string>();
	obstacle.m_rotation = obstacleNode["rotation"].as<float>();
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

void operator >> (const YAML::Node &waypointNode, Waypoint &waypoint)
{
	waypoint.m_position.x = waypointNode["position"]["x"].as<float>();
	waypoint.m_position.y = waypointNode["position"]["y"].as<float>();
	waypoint.m_speed = waypointNode["speed"].as<float>();
}

void operator >> (const YAML::Node &waypointNode, StartPositionData &startPositionData)
{
	startPositionData.m_position.x = waypointNode["position"]["x"].as<float>();
	startPositionData.m_position.y = waypointNode["position"]["y"].as<float>();
}

void operator >> (const YAML::Node & carNode, CarData & carDataIn)
{
	carDataIn.m_acceleration = carNode["acceleration"].as<float>();
	carDataIn.m_deceleration = carNode["deceleration"].as<float>();
	carDataIn.m_turnRate = carNode["turnrate"].as<float>();
	carDataIn.m_name = carNode["name"].as<std::string>();
	carDataIn.m_texture = carNode["texture"].as<std::string>();
	carDataIn.m_enemy = carNode["enemy"].as<bool>();
}

void operator >> (const YAML::Node &cupNode, CupData &cupData)
{
	cupData.m_name = cupNode["name"].as<std::string>();
	cupData.m_texture = cupNode["texture"].as<std::string>();
}

void operator >> (const YAML::Node &checkpointNode, CheckpointData &checkpointData)
{
	checkpointData.m_name = checkpointNode["name"].as<std::string>();
	checkpointData.m_texture = checkpointNode["texture"].as<std::string>();
	checkpointData.m_textureRect.left = checkpointNode["texturerect"]["left"].as<int>();
	checkpointData.m_textureRect.top = checkpointNode["texturerect"]["top"].as<int>();
	checkpointData.m_textureRect.width = checkpointNode["texturerect"]["width"].as<int>();
	checkpointData.m_textureRect.height = checkpointNode["texturerect"]["height"].as<int>();
	checkpointData.m_rotation = checkpointNode["rotation"].as<float>();
}

void operator >> (YAML::Node &baseNode, LevelData &levelIn)
{
	baseNode["player"] >> levelIn.m_playerData;
	const YAML::Node& obstaclesNode = baseNode["obstacles"].as<YAML::Node>();
	for (unsigned i = 0; i < obstaclesNode.size(); ++i)
	{
		ObstacleData obstacle;
		obstaclesNode[i] >> obstacle;
		levelIn.m_obstacleDataVector.push_back(obstacle);
	}

	const YAML::Node& textureNode = baseNode["textures"].as<YAML::Node>();
	for (unsigned int i = 0; i < textureNode.size(); ++i)
	{
		TextureData texture;
		textureNode[i] >> texture;
		levelIn.m_textureDataVector.push_back(texture);
	}

	const YAML::Node& waypointsNode = baseNode["waypoints"].as<YAML::Node>();
	for (unsigned int i = 0; i < waypointsNode.size(); ++i)
	{
		Waypoint waypoint;
		waypointsNode[i] >> waypoint;
		levelIn.m_waypoints.push_back(waypoint);
	}

	const YAML::Node& startPosNode = baseNode["startPositions"].as<YAML::Node>();
	for (unsigned int i = 0; i < startPosNode.size(); ++i)
	{
		StartPositionData startPosData;
		startPosNode[i] >> startPosData;
		levelIn.m_startPositionData.push_back(startPosData);
	}

	const YAML::Node& carsNode = baseNode["cars"].as<YAML::Node>();
	for (unsigned int i = 0; i < carsNode.size(); ++i)
	{
		CarData carData;
		carsNode[i] >> carData;
		if (carData.m_enemy)
		{
			levelIn.m_enemyCarData.push_back(carData);
		}
		else
		{
			levelIn.m_carData.push_back(carData);
		}
		
	}

	const YAML::Node& cupsNode = baseNode["cups"].as<YAML::Node>();
	for (unsigned int i = 0; i < cupsNode.size(); ++i)
	{
		CupData cupData;
		cupsNode[i] >> cupData;
		levelIn.m_cupData.push_back(cupData);
	}

	const YAML::Node& checkpointsNode = baseNode["checkpoints"].as<YAML::Node>();
	for (unsigned int i = 0; i < checkpointsNode.size(); ++i)
	{
		CheckpointData checkData;
		checkpointsNode[i] >> checkData;
		levelIn.m_checkpointData.push_back(checkData);
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