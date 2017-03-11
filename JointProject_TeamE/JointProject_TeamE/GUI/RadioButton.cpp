#include "RadioButton.h"

/// <summary>
/// Constructor function for the RadioButton class
/// </summary>
/// <param name="focusColorIn">Focus color used for the radio button</param>
/// <param name="noFocusColorIn">No focus color used by the radio button</param>
/// <param name="fillColorIn">Fill color used by the radio button</param>
/// <param name="selectSoundIn">Sound used by the radio button</param>
/// <param name="textIn">Text to be displayed by the RadioButton object's inherited Label</param>
/// <param name="parent">Parent widget to the RadioButton object</param>
/// <param name="positionIn">Position of the RdaioButton</param>
/// <param name="radGroup">A vector containing radio buttons, considered the radio button group and switching one radio button willaffect them all</param>
/// <param name="startPos">The start position of the transition</param>
/// <param name="endPos">The end position of the transition</param>
/// <param name="characterSize">Size of the Font used for drawing the text in the Label</param>
/// <param name="boxWidth">Width of the RadioButton Box</param>
/// <param name="boxHeight">Height of the RadioButton box</param>
RadioButton::RadioButton(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, const std::string & textIn, Widget * parent, sf::Vector2f & positionIn,
	std::vector<RadioButton *> & radGroup, sf::Vector2f &startPos, sf::Vector2f &endPos, 
	int characterSize, float boxWidth, float boxHeight)
		: Label(textIn, parent, characterSize), m_otherButtons(radGroup),
	focusColor(focusColorIn),
	noFocusColor(noFocusColorIn),
	fillColor(fillColorIn)
{
	// Set the position of the inherited Widget
	widgetPos = positionIn;
	widgetStartPos = startPos;
	widgetEndPos = endPos;
	// Set the position, size, colour and outline of the RadioButton Box
	m_radioButtonRect.setPosition(widgetPos);
	m_radioButtonRect.setSize(sf::Vector2f(boxWidth, boxHeight));
	m_radioButtonRect.setFillColor(sf::Color::White);
	m_radioButtonRect.setOutlineColor(sf::Color::White);
	m_radioButtonRect.setOutlineThickness(3.f);
	// Set the position of the Label
	// We offset the Label to be directly above the RadioButton
	sf::Vector2f textOffset(widgetPos.x, widgetPos.y - m_radioButtonRect.getGlobalBounds().height);
	m_radioButtonRect.setOrigin(m_radioButtonRect.getLocalBounds().width / 2.0f, m_radioButtonRect.getLocalBounds().height / 2.0f);
	Label::setPosition(textOffset);
}

/// <summary>
/// Sets the position of the button at it's origin
/// </summary>
/// <param name="position">The position origin of the button</param>
void RadioButton::setPosition(sf::Vector2f &position)
{
	widgetPos = position;
	m_radioButtonRect.setPosition(widgetPos);
	// Set the position of the Label
	// We offset the Label to be directly above the RadioButton
	sf::Vector2f textOffset(widgetPos.x, widgetPos.y - m_radioButtonRect.getGlobalBounds().height);
	Label::setPosition(textOffset);
}

/// <summary>
/// Processes the input from a controller / keyboard and updates the RadioButton as well as other widgets
/// </summary>
/// <param name="controller">Controller object used for checking input</param>
/// <returns>Bool to tell whether the input was used or not</returns>
bool RadioButton::processInput(XboxController & controller)
{
	if (!m_hasFocus)
	{
		// If the RadioButton is out of focus then set the color to Cyan
		m_radioButtonRect.setOutlineColor(noFocusColor);
		return false;
	}
	else
	{
		// Otherwise set it to Magenta
		m_radioButtonRect.setOutlineColor(focusColor);
		if (controller.isButtonPressed(XBOX360_UP)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (m_up != nullptr)
			{
				// Set the button above *this to be in focus
				m_up->promoteFocus();
				// Set the check box to be out of focus
				demoteFocus();
				return true;
			}
		}
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
		else if (controller.isButtonPressed(XBOX360_LEFT)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (m_left != nullptr)
			{
				m_left->promoteFocus();
				demoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_RIGHT)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (m_right != nullptr)
			{
				m_right->promoteFocus();
				demoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_A)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			for (RadioButton * radioButton : m_otherButtons)
			{
				// De-activate all other radio buttons in a group
				radioButton->deActivate();
			}
			// Set this radio button on
			m_state = true; 
			// Change the color of the radio button
			m_radioButtonRect.setFillColor(fillColor); 
			try
			{
				// Callback function
				select();
			}
			catch (std::bad_function_call){}
		}
	}
}

/// <summary>
/// Draw function allows the window to draw the object directly
/// </summary>
/// <param name="target">Targets used for drawing</param>
/// <param name="states">States used for drawing</param>
void RadioButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Draw the radioButton Rectangle
	target.draw(m_radioButtonRect);
	// Draw the inherited Label
	Label::draw(target, states);
}

/// <summary>
/// Function simply sets the m_state bolean to false and changes the fillcolor
/// </summary>
void RadioButton::deActivate()
{
	// Change the fill color
	m_radioButtonRect.setFillColor(sf::Color::White);
	// Set the state to false
	m_state = false;
}

/// <summary>
/// Simple getter method for the m_state member variable
/// </summary>
/// <returns>The state of the RadioButton</returns>
bool RadioButton::getState() const
{
	return m_state;
}

/// <summary>
/// Function used to set the state of a radiobutton
/// </summary>
/// <param name="stateIn">The state you want to set the radioButton to</param>
void RadioButton::activate()
{
	m_radioButtonRect.setFillColor(fillColor);
	m_state = true;
	for (auto & otherRadioButton : m_otherButtons)
	{
		if (otherRadioButton != this)
		{
			// This is done so as to ensure that no two radio buttons in a set are ever on similtaneously
			otherRadioButton->deActivate();
		}
	}
}

/// <summary>
/// Function used to reset all of the colours used by the radio button if those colours are changed
/// </summary>
void RadioButton::setColors()
{
	if (m_hasFocus)
	{
		m_radioButtonRect.setOutlineColor(focusColor);
	}
	else
	{
		m_radioButtonRect.setOutlineColor(noFocusColor);
	}
	if (m_state)
	{
		m_radioButtonRect.setFillColor(fillColor);
	}
	else
	{
		m_radioButtonRect.setFillColor(sf::Color::White);
	}
}