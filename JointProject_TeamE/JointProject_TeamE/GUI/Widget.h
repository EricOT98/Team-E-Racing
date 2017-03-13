/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef WIDGET_H
#define WIDGET_H

#include <SFML\Graphics.hpp>
#include "..\Input\XboxController.h"

/// <summary>
/// Brief: Provides a base class for objects that are a widget
///
/// Detail: Allows the subclasses to overload the how the player will control a
/// widget, render it and how it's updated. Provides pointers to other widgets
/// which hold the relative location of the next gui the player can move to
/// </summary>
class Widget : public sf::Drawable
{
public:
	Widget(Widget *parent = nullptr);

	virtual bool processInput(XboxController &controller);
	virtual void update();
	virtual void updateShape();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Parent widget
	Widget *m_parent;

	// Pointers to adjacent widgets
	Widget *m_left;
	Widget *m_right;
	Widget *m_up;
	Widget *m_down;

	void promoteFocus();
	void demoteFocus();
	bool getFocus();
	virtual void setPosition(sf::Vector2f &pos);
	virtual void setColors();
	sf::Vector2f getPosition();
	sf::Vector2f getStartPos();
	sf::Vector2f getEndPos();

protected:
	sf::Vector2f widgetPos;
	bool m_hasFocus; // The widget the player is currenly on and can interact with
	sf::Vector2f widgetStartPos, widgetEndPos;
};

#endif