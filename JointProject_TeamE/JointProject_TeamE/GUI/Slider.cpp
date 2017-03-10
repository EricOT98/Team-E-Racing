#include "Slider.h"

/// <summary>
/// Constructor function for the slider class
/// </summary>
/// <param name="focusColorIn">Focus color used by the slider</param>
/// <param name="noFocusColorIn">No focus color used by the slider</param>
/// <param name="fillColorIn">Fill color used by the slider</param>
/// <param name="selectSoundIn">Sound used by the slider</param>
/// <param name="text">Text to be displayed by the inherited Label</param>
/// <param name="parent">parent widget for the class</param>
/// <param name="position">position of the slider</param>
/// <param name="characterSize">Size of the font used for drawing the text</param>
/// <param name="sliderWidth">Width of the slider</param>
/// <param name="sliderHeight">Height of the slider</param>
/// <param name="startPos">The start position of the transition</param>
/// <param name="endPos">The end position of the transition</param>
Slider::Slider(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, const std::string& text, Widget* parent, sf::Vector2f &position, int characterSize, float sliderWidth,
	float sliderHeight, sf::Vector2f &startPos, sf::Vector2f &endPos)
	: Label(text, parent, characterSize), m_barBaseWidth(sliderWidth), m_barSize(m_barBaseWidth), m_barBaseHeight(sliderHeight), 
	focusColor(focusColorIn),
	noFocusColor(noFocusColorIn),
	fillColor(fillColorIn)
{
	widgetPos = position;
	widgetStartPos = startPos;
	widgetEndPos = endPos;

	// Base under the moving slider bar
	m_base.setSize(sf::Vector2f(m_barBaseWidth, m_barBaseHeight));
	m_base.setOutlineThickness(2);
	m_base.setPosition(widgetPos);

	// The slider bar the player changes
	m_bar.setFillColor(fillColor);
	m_bar.setSize(sf::Vector2f(m_barSize, m_barBaseHeight));
	m_bar.setPosition(widgetPos);
	m_base.setOrigin(m_base.getLocalBounds().width / 2.0f, m_base.getLocalBounds().height / 2.0f);
	m_bar.setOrigin(m_base.getLocalBounds().width / 2.0f, m_base.getLocalBounds().height / 2.0f);
	Label::setPosition(position - sf::Vector2f(0.0f, 30.0f));
}

/// <summary>
/// Sets the position of the button at it's origin
/// </summary>
/// <param name="position">The position origin of the button</param>
void Slider::setPosition(sf::Vector2f &position)
{
	widgetPos = position;
	m_base.setPosition(widgetPos);
	m_bar.setPosition(widgetPos);
	Label::setPosition(position - sf::Vector2f(0.0f, 30.0f));
}

/// <summary>
/// Processes the input from a controller / keyboard and updates the CheckBox as well as other widgets
/// </summary>
/// <param name="controller">Controller object used for checking input</param>
/// <returns>Bool to tell whether the input was used or not</returns>
bool Slider::processInput(XboxController &controller)
{
	if (!m_hasFocus)
	{
		// Set the outline color to Cyan if the Widget is out of focus
		m_base.setOutlineColor(noFocusColor);
		return false;
	}
	if (m_hasFocus)
	{
		// Otherwise set the color to Magenta
		m_base.setOutlineColor(focusColor);
		// Right input
		if (controller.isButtonHeldDown(XBOX360_RIGHT)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (m_barSize < m_barBaseWidth - 2)
			{
				// Increase the bar size
				m_barSize += 2.0f;
			}
			else
			{
				m_barSize = m_barBaseWidth;
			}
			try 
			{
				// Call the associated callback function
				increase();
			}
			catch (std::bad_function_call &e){}
			// Set the new size of the bar
			m_bar.setSize(sf::Vector2f(m_barSize, m_barBaseHeight));
			return true;
		}
		// Left input
		else if (controller.isButtonHeldDown(XBOX360_LEFT)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (m_barSize >= 2)
			{
				// Decrease the bar size
				m_barSize -= 2.0f; 
			}
			else
			{
				m_barSize = 0.f;
			}
			try
			{
				// Call the associtaed callback function
				decrease();
			}
			catch (std::bad_function_call &e){}
			// Set the new size of the bar
			m_bar.setSize(sf::Vector2f(m_barSize, m_barBaseHeight)); 
			return true;
		}
		// Up input
		else if (controller.isButtonPressed(XBOX360_UP) 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (m_up != nullptr)
			{
				// Set the button above *this to be in focus
				m_up->promoteFocus();
				// Set the slider to be out of focus
				demoteFocus();
				return true;
			}
		}
		// Down input (See up input)
		else if (controller.isButtonPressed(XBOX360_DOWN)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (m_down != nullptr)
			{
				m_down->promoteFocus();
				demoteFocus();
				return true;
			}
		}
	}
}

/// <summary>
/// Draw function allows the window to draw the object directly
/// </summary>
/// <param name="target">Targets used for drawing</param>
/// <param name="states">States used for drawing</param>
void Slider::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Call the super class overridden draw function.
	Label::draw(target, states);

	// Draw the slider.
	target.draw(m_base);
	target.draw(m_bar, states);
}

/// <summary>
/// Function simply returns how full the slider bar is as a percentage   
/// </summary>
/// <returns>The percentage of the slider Bar that is full as a float</returns>
float Slider::getPercentageFull()
{
	// Simple conversion to a percentage
	return (m_barSize / m_barBaseWidth);
}

/// <summary>
/// Function allows the sliders bar size to be set
/// </summary>
/// <param name="percentageIn">A value between zero and one representing how full the slider is</param>
void Slider::setPercentageFull(float percentageIn)
{
	m_barSize = percentageIn * m_barBaseWidth;
	m_bar.setSize(sf::Vector2f(m_barSize, m_barBaseHeight));
}

/// <summary>
/// Set the colors of the Slider
/// </summary>
void Slider::setColors()
{
	if (m_hasFocus)
	{
		// If the slider is in focus set the outline to focus color
		m_base.setOutlineColor(focusColor);
	}
	else
	{
		// otherwise set it to no focus color
		m_base.setOutlineColor(noFocusColor);
	}
	// Set the fill color
	m_bar.setFillColor(fillColor);
}

/// <summary>
/// Simple getter function for m_hasFocus
/// </summary>
/// <returns>the focus state of the slider</returns>
bool Slider::getFocus()
{
	return m_hasFocus;
}