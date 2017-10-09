#ifndef GAMESTATE_H
#define GAMESTATE_H

/**
* \brief gameState is strongly typed enum class 
* It is used to classify the status of the game in order to display the necessary splash screens
*/
enum class gameState
{
	win =0,
	lose,
	playing,
};

#endif