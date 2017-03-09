/// <summary>
/// Author: Eric O' Toole
/// Description: A basic class for a racer object that will contain a car and name
/// thus allowing multiple different racers to be processed the same way
/// 
/// Date Started: 09/03/17
/// Time Taken: 20 minutes
/// Known Errors:No known Errors
/// TODO: Implement car class to allow
/// </summary>

#ifndef RACER_H
#define RACER_H

#include <SFML\Graphics.hpp>

class Racer
{
public:
	Racer();
	~Racer();

	void setCar();
	void setName(std::string name);
	virtual void update();
	virtual void render(sf::RenderWindow & window);
	virtual void processInput(sf::Event &e);

protected:
	std::string m_name;
};

#endif
