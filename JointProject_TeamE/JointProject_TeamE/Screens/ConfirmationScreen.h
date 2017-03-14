#ifndef CONFIRMATION_SCRREN_H
#define CONFIRMATION_SCRREN_H

#include "Screen.h"

class ConfirmationScreen : public Screen
{
public:
	ConfirmationScreen();
	~ConfirmationScreen();

	void update(XboxController & controller) override;
	void reset() override;

private:
	void yesButtonCallback();
	void noButtonCallback();

	// GUI elements
	Label *m_confirmationLabel;
	Label *m_areYouSureLabel;
	Button *m_yesButton;
	Button *m_noButton;

	bool m_yesButtonSelected;
	bool m_noButtonSelected;

	bool m_transitionIn;
	float m_interpolation;
};


#endif