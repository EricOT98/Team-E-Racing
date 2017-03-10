/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef SLIDER_H
#define SLIDER_H

#include "Label.h"
#include <SFML\Audio\Sound.hpp>
#include <functional>	// Callback functions

/// <summary>
/// Slider class used for creating Sliders onscreen
/// 
/// Sliders are a widget that have a min and max value which the 
/// player can change.
/// </summary>
class Slider : public Label
{
public:
	Slider(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, const std::string& text, Widget* parent, sf::Vector2f &position, int characerSize = 18.0f, float sliderWidth = 100.0f,
		float sliderHeight = 15.0f, sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f());
	bool processInput(XboxController & controller);
	virtual void setPosition(sf::Vector2f &position) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	float getPercentageFull();
	void setPercentageFull(float percentageIn);
	void setColors() override;
	bool getFocus();

	// Callback function to link to external functions
	typedef std::function<void()> Callback;
	Callback increase, decrease;

private:
	// Rectangles ot draw
	sf::RectangleShape m_bar, m_base;

	//Rectangle attributes
	float m_barBaseWidth;
	float m_barBaseHeight;
	float m_barSize;

	sf::Color focusColor;
	sf::Color noFocusColor;
	sf::Color fillColor;
};

#endif