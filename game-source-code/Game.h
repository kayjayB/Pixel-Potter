#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "Player.h"
#include "Window.h"
#include "Enemy.h"
#include "EntityList.h"
#include "Clock.h"
#include "CollisionManager.h"
#include "entityCreator.h"

/**
* \brief Game class - handles all of the logic required in the operating of the game
*/
class Game
{
public:
	/**
	* \brief Default Constructor. Creates a Game object
	*/
    Game();
	/**
	* \brief Destructor
	*/
    ~Game();
	
private:
	/**
	* \brief Function ot control the game loop.
	* The function calls the Update, Render, RestartClock functions
	*/	
	void GameLoop();
	/**
	* \brief Function that updates all of the entities involved in the game.
	* This includes calling the functions that create the various enemy entities, updating the 
	* positions of the entities, calling the function that checks for collisions, calling the 
	* function that deletes expired entities
	*/
    void Update();
	/**
	* \brief Function that renders the movingEntity objects to the screen.
	* The function loops through the vector of movingEntity and calls the Window show() function 
	* on each entity
	*/
    void Render();
	/**
	* \brief Function that calls the Clock RestartClock function
	*/	
    void RestartClock();
	/**
	* \brief Function that resets all the necessary variables upon restarting a new game
	*/	
	void Reset();
	/**
	* \brief Function that calls the Clock GetTime function
	*/	
	float GetTime();
	
    float _elapsedTime;
    bool _bulletExists;
	const int MAXENEMIES=20;
	
	std::shared_ptr< Clock> gameClock{new Clock{}};
	std::shared_ptr <Player> playerPtr{ new Player{}};
	Window window;
	CollisionManager collision;
	entityCreator _create;
	
};

#endif
