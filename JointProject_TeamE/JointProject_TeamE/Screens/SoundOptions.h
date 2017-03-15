/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef SOUND_OPTIONS_H
#define SOUND_OPTIONS_H

#include "Screen.h"

/// A menu displaying all the options assocaite with sound
/// 
/// The Sound Options screen handles all the neccesary widgets on screen
/// and updates the player input and screen navigation
class SoundOptions : public Screen
{
public:
	SoundOptions();
	~SoundOptions();
	
	void update(XboxController & controller) override;
	void reset() override;

private:
	void musicSliderCallback();
	void effectsSliderCallback();
	void muteCallback();
	void backButtonCallback();

	Label *m_titleLabel;
	Slider *m_musicSlider;
	Slider *m_effectSlider;
	CheckBox *m_muteCheckBox;
	Button *m_backButton;

	bool m_backButtonSelected;
};

#endif