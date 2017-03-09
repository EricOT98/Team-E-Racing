/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>


/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Label.h"
#include <functional>

/// <summary>
/// Brief: CheckBox Class used for creating Check Boxes onscreen
/// 
/// Detail: Class inherits from Label and thus is a widget
/// </summary>
class CheckBox : public Label {
public:
	CheckBox();
	CheckBox(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &selectSoundIn, const std::string & textIn, Widget * parent, sf::Vector2f & positionIn, int characterSize = 22.f, float boxWidth = 40.f,
		float boxHeight = 40.f, sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f());
	bool processInput(XboxController & controller);
	virtual void setPosition(sf::Vector2f &position) override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	bool getFocus();
	bool getState();
	void switchState();
	void setState(bool stateIn);
	void setColors() override;

	// Callback function to link to external functions
	typedef std::function<void()> Callback;
	Callback select, up, down, left, right;
private:
	bool m_state = false;
	sf::RectangleShape m_checkBoxRect;
	// Assets
	sf::Sound &selectSound;
	sf::Color &focusColor;
	sf::Color &noFocusColor;
	sf::Color &fillColor;
};

#endif