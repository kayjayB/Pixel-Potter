#ifndef USERINPUT_H
#define USERINPUT_H

/**
* \brief userInput is strongly typed enum class 
* It is used to classify the user's input independent of the interface layer
*/
enum class userInput
{
	PressLeft,
	PressRight,
	NoButtonPress,
	PressSpace,
};

#endif