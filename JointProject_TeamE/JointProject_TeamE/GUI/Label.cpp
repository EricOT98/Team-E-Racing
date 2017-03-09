#include "Label.h"

/// <summary>
/// Constructor function for the Label class
/// </summary>
/// <param name="text">Text to be displayed by the Label</param>
/// <param name="parent">parent widget to the label</param>
/// <param name="size">Font size of the Label</param>
/// <param name="startPos">The start position of the transition</param>
/// <param name="endPos">The end position of the transition</param>
Label::Label(const std::string& text, Widget* parent, unsigned int size, sf::Vector2f &startPos, sf::Vector2f &endPos) 
	: Widget(parent)
{
	widgetStartPos = startPos;
	widgetEndPos = endPos;

	// TODO(Darren): User resource manager to get font
	//m_text.setFont(*g_resourceMgr.getGameFont()); // Set the font
	//Set the text attributes
	setText(text);
	setTextColor(sf::Color::White);
	m_text.setCharacterSize(size);
	textRect = m_text.getGlobalBounds();
	updateShape();

	sf::Text fontCheck;
	/* 
		We use this to make sure the heigh of the buttons is constant as the 
	    bounding box ia affected by ascenders and descenders in strings so
	    the true text height is the maximum height possible
	*/
	fontCheck.setFont(*m_text.getFont());
	fontCheck.setCharacterSize(size);
	fontCheck.setString("ph|");
	m_trueTextHeight = fontCheck.getGlobalBounds().height;
	m_text.setOrigin(textRect.width / 2.0f,
		m_trueTextHeight / 2.f);
}

/// <summary>
/// Function simply sets the string for the text object
/// </summary>
/// <param name="text">string to be displayed</param>
void Label::setText(const std::string& text)
{
	m_text.setString(text);
	updateShape();
}

/// <summary>
/// Function simply sets the position of the text object
/// </summary>
/// <param name="relativePosition"></param>
void Label::setPosition(sf::Vector2f &position)
{
	m_text.setPosition(position);
	widgetPos = position;
}

/// <summary>
/// Function simply gets the character size used by the text object
/// </summary>
/// <returns></returns>
unsigned int Label::getCharacterSize() const
{
	return m_text.getCharacterSize();
}

/// <summary>
/// Set the color of the Text
/// </summary>
/// <param name="color">The desired text color</param>
void Label::setTextColor(const sf::Color& color)
{
	m_text.setColor(color);
}

/// <summary>
/// Draw function allows the window to draw the object directly
/// </summary>
/// <param name="target">Targets used for drawing</param>
/// <param name="states">States used for drawing</param>
void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_text, states);
}

/// <summary>
/// Function simply returns the text object
/// </summary>
/// <returns>Text object</returns>
sf::Text Label::getText()
{
	return m_text;
}

/// <summary>
/// Function simply returns the maximum possible height for the bounding
/// </summary>
/// <returns>Max possible height of the text bounding rectangle</returns>
float Label::getTextHeight()
{
	return m_trueTextHeight;
}