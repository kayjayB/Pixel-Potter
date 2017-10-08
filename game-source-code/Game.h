#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "Player.h"
#include "Window.h"
#include "Enemy.h"
#include "EntityList.h"
#include "Clock.h"
#include "CollisionManager.h"
#include "entityCreator.h"

/**
* Game class - handles all the logic required in the operating of the game
*/
class Game
{
public:
	/**
	* Default Constructor. Creates a Game object
	*/
    Game();
	/**
	* Destructor
	*/
    ~Game();
	/**
	* Function that updates all of the entities involved in the game.
	* This includes calling the functions that create the various enemy entities, updating the 
	* positions of the entities, calling the function that checks for collisions, calling the 
	* function that deletes expired entities
	*/
    void Update();
	/**
	* Function that renders the movingEntities to the screen.
	* The function loops through the vector of movingEntity and calls the Window draw function 
	* on each entity
	*/
    void Render();
	/**
	* Function that returns a pointer to the Window class
	* @return Window pointer
	*/
    Window* GetWindow();
	/**
	* Function that calls the Clock RestartClock function
	*/	
    void RestartClock();
	
private:
	/**
	* Function that resets all the necessary variables upon restarting a new game
	*/	
	void Reset();
	/**
	* Function that calls the Clock GetTime function
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

#endif // GAME_H
