///// <summary>
///// @author Darren Sweeney
///// @version 1.0
///// </summary>
//
//#ifndef SOUND_OPTIONS_H
//#define SOUND_OPTIONS_H
//
//#include "Screen.h"
//#include "..\Input\XboxController.h"
//#include "..\GUI\Button.h"
//#include "..\GUI\Slider.h"
//#include "..\GUI\CheckBox.h"
//#include "..\GUI\Gui.h"
//
///// A menu displaying all the options assocaite with sound
///// 
///// The Sound Options screen handles all the neccesary widgets on screen
///// and updates the player input and screen navigation
//class SoundOptions : Screen
//{
//public:
//	SoundOptions();
//	~SoundOptions();
//	
//	void update();
//	void render(sf::RenderWindow &window);
//	void processInput(XboxController &controller);
//
//private:
//	void checkScreenTransition(Button *button, GameScreenState stateToChangeTo);
//
//	Gui m_soundOpitionsGUI;
//	Label *m_titleLabel;
//	Slider *m_musicSlider;
//	Slider *m_effectSlider;
//	CheckBox *m_muteCheckBox;
//	Button *m_backButton;
//};
//
//#endif