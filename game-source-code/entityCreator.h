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
* \brief entityCreator class - handles the creation of all of the enemy entities (Enemy, LaserGenerator,
* LaserArc, Asteroid, Satellite)
*/
class entityCreator
{
public:
	/**
	* \brief Constructor. Creates an entityCreator object
	* @param gameClock is a shared pointer to a Clock object
	* @param maxEnemies is an int containing the maximum number of enemies to be created
	* @param playerPtr is a shared pointer to the Player object
	*/
	entityCreator(const std::shared_ptr <Clock> &gameClock, int maxEnemies, const std::shared_ptr <Player> &playerPtr);
	/**
	* \brief Destructor
	*/
	~entityCreator();
	/**
	* \brief Function to create all of the various enemy entities
	*/	
	void create();
	/**
	* \brief Function to reset the required variables upon restarting the game
	*/
	void reset();
	
private:	
	/**
	* \brief Function to create Enemy entities
	*/
	void CreateEnemy();
	/**
	* \brief Function to create Asteroid entities
	*/
	void CreateAsteroid();
	/**
	* \brief Function to create Satellite entities
	*/
	void CreateSatellite();
	/**
	* \brief Function to create LaserGenerator and LaserArc entities
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
