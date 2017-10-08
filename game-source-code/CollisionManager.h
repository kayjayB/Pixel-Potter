#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <memory>

#include "movingEntity.h"
#include "Player.h"
#include "Window.h"
#include "gameState.h"

/**
* CollisionManager class - used to check collisions between entities and manage the deletions of entities
*/
class CollisionManager
{
public:
    /**
    * Default constructor. Creates a CollisionManager object
    */
    CollisionManager();
    /**
    * Default destructor
    */
    ~CollisionManager();
    /**
    * Function to check all the collisions of the required entities
    */
    void checkCollision();
    /**
    * Function to check if two entities have collided
	* @param i is an integer containing the index of an entity
	* @param j is an integer containing the index of the other entity
	* @return bool true if a collision has occured and false otherwise
    */
    bool Collision(int i, int j);
	/**
    * Function to delete entities that have collided, or are no longer valid
	* @param playerPtr is a shared pointer to the player object
	* @param j is an integer containing the index of the other entity
	* @return bool true if a collision has occured and false otherwise
    */
    gameState entityCleanUp(std::shared_ptr<Player> playerPtr);

private:
    bool _collidedArc;
};

#endif // COLLISIONMANAGER_H
