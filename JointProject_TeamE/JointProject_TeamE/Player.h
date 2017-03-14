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
#include "Input\XboxController.h"
#include "Input\KeyboardHandler.h"

class Player : public Racer
{
public:
	Player(XboxController & controllerIn);
	~Player();
	void initialise();
	void update(float dt) override;
protected:
	int m_racePosition;
	bool m_alive;
	XboxController & m_controller;
};

#endif
