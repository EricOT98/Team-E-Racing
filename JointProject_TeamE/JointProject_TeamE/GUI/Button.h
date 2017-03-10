/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"
#include <SFML\Audio\Sound.hpp>
#include <functional>

/// <summary>
/// Button Class used for creating buttons onscreen.
/// 
/// Allows a button to be pressed by the player to create a on/off event.
/// </summary>
class Button : public Label 
{
public:
	Button(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, 
		const std::string & textIn, Widget * parent, sf::Vector2f & positionIn, int characterSize = 18.f, float buttonWidth = 100.f,
		float buttonHeight = 40.f, sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f());
	bool processInput(XboxController & xboxController);
	virtual void setPosition(sf::Vector2f &position) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setColors() override;
	// Callback function to link to external functions
	typedef std::function<void()> Callback;
	Callback select;
private:
	sf::RectangleShape m_buttonRect;
	// Buffer for increasing the edge of the button slightly
	const int BUTTON_BUFFER = 15;
	// Assets
	sf::Color &focusColor;
	sf::Color &noFocusColor;
	sf::Color &fillColor;
};
#endif
