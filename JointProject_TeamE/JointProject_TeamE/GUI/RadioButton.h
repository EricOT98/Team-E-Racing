/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>


#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "Label.h"
#include <SFML\Audio\Sound.hpp>
#include <functional>

/// <summary>
/// RadioButton class used for creating radioButtons
/// 
/// A RadioButton contains an on off value and a reference to other RadioButton 
/// that will share state.
/// </summary>
class RadioButton : public Label 
{
public:
	RadioButton(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, 
		sf::Sound &selectSoundIn, const std::string & textIn, Widget * parent, 
		sf::Vector2f & positionIn, std::vector<RadioButton *> & radGroup,
		sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f(), 
		int characterSize = 22.f, float boxWidth = 40.f, float boxHeight = 40.f);
	bool processInput(XboxController & controller);
	virtual void setPosition(sf::Vector2f &position) override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void deActivate();
	bool getState() const;
	void activate();
	void setColors() override;

	// Callback function to link to external functions
	typedef std::function<void()> Callback;
	Callback select;
private:
	// State of the radio button
	bool m_state = false;
	// Rectangle displayed by the radio button
	sf::RectangleShape m_radioButtonRect;
	// A reference to a vector containing the radio button group
	std::vector<RadioButton *> & m_otherButtons;

	// Sound and Color references
	sf::Sound &selectSound;
	sf::Color &focusColor;
	sf::Color &noFocusColor;
	sf::Color &fillColor;
};

#endif
