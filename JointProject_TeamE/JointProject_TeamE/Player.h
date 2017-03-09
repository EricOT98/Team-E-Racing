/// <summary>
/// Author: Eric O' Toole
/// Description: A basic player class that allows control 
/// of a a car the player has as well as storing their 
/// relative information
/// 
/// Date Started: 09/03/17
/// Time Taken: 20 minutes
/// 
/// Known Errors: No Known errors
/// TODO: Implement the Car class to allow functionality to
/// be put in Player
/// </summary>

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>
#include <iostream>

#include "Racer.h"

class Player : public Racer
{
public:
	Player();
	~Player();
	void initialise();
	void update() override;
	void render(sf::RenderWindow & window) override;
	void processInput(sf::Event &e) override;

	void setRacePosition(int pos);
protected:
	int m_racePosition;
	bool m_alive;
};

#endif
