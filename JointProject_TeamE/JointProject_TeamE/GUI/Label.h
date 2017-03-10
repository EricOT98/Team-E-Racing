/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef LABEL_H
#define LABEL_H

#include <SFML\Graphics.hpp>
#include "Widget.h"
#include "..\ResourceManager.h"

/// <summary>
/// Label class used to draw Labels (Text) to the screen
///
/// Renders text on screen based on the character size, postion and color specified
/// </summary>
class Label : public Widget
{
public:
	Label(const std::string& text, Widget* parent = nullptr, unsigned int size = 18, 
		sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f());
	virtual void setPosition(sf::Vector2f &position) override;
	void setText(const std::string &text);
	unsigned int getCharacterSize() const;
	void setTextColor(const sf::Color& color);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Text getText();
	float getTextHeight();
private:
	sf::FloatRect textRect;
	sf::Text m_text;
	sf::Font m_font;
	float m_trueTextHeight;
};

#endif