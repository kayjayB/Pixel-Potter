#ifndef ENTITYCREATOR_H
#define ENTITYCREATOR_H

#include "Clock.h"
#include "movingEntity.h"
#include "Enemy.h"
#include "EntityList.h"
#include "Asteroid.h"
#include "Satellite.h"
#include "Player.h"
#include "LaserGenerator.h"
#include "LaserArc.h"

/**
* entityCreator class - handles the creation of all of the enemy entities (Enemy, LaserGenerator,
* LaserArc, Asteroid, Satellite)
*/
class entityCreator
{
public:
	/**
	* Constructor. Creates an entityCreator object
	* @param gameClock is a shared pointer to a Clock object
	* @param maxEnemies is an int containing the maximum number of enemies to be created
	* @param playerPtr is a shared pointer to the player object
	*/
	entityCreator(std::shared_ptr <Clock> gameClock, int maxEnemies, std::shared_ptr <Player> playerPtr);
	/**
	* Destructor
	*/
	~entityCreator();
	/**
	* Function to create all of the enemy entities
	*/	
	void create();
	/**
	* Function to reset the required variables upon restarting the game
	*/
	void reset();
	
private:	
	/**
	* Function to create Enemy entities
	*/
	void CreateEnemy();
	/**
	* Function to create Asteroid entities
	*/
	void CreateAsteroid();
	/**
	* Function to create Satellite entities
	*/
	void CreateSatellite();
	/**
	* Function to create LaserGenerator and LaserArc entities
	*/
	void CreateLaser();
	
	std::shared_ptr <Clock> _entityClock;
	std::shared_ptr <Player> _playerPtr;
	float _timeEnemy;
	float _timeAsteroid;
	float _timeSatellite;
	float _generateAsteroid;
	float _generateEnemy;
	int _MAXENEMIES;
	
	
};

#endif
