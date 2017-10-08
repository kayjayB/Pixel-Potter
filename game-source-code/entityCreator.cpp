#include "entityCreator.h"

entityCreator::entityCreator(std::shared_ptr <Clock> gameClock, int maxEnemies, std::shared_ptr <Player> playerPtr):
_entityClock{gameClock},
_playerPtr{playerPtr},
_MAXENEMIES{maxEnemies}
{
	_timeAsteroid=0.0;
	_timeEnemy=0.0;
	_timeSatellite=0.0;
	_generateAsteroid= fmod(rand(),5.0)+1;
	_generateEnemy= 1;
}

entityCreator::~entityCreator()
{
}

void entityCreator::create()
{
	CreateEnemy();
	CreateAsteroid();
	CreateSatellite();
	CreateLaser();
}

void entityCreator::CreateEnemy()
{
	
_timeEnemy+=_entityClock->GetTime();
_generateEnemy=fmod(rand(),4)+_timeEnemy;
if ( Enemy::getNumberofEnemiesAlive() < 3 )
	{
	if (_timeEnemy > (_generateEnemy - 1) && _timeEnemy < (_generateEnemy+1) && Enemy::getTotalNumberofEnemies()<_MAXENEMIES)
	{
		std::shared_ptr <Enemy> enemyPtr{ new Enemy{}};
		movingEntity::entityList.push_back(enemyPtr);
	}
}
}

void entityCreator::CreateAsteroid()
{

_timeAsteroid=_entityClock->getAsteroidTime();
	if (_timeAsteroid > (_generateAsteroid - 0.5) && _timeAsteroid < (_generateAsteroid+0.5))
	{
		
		std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{_playerPtr->getAngle()}};
		movingEntity::entityList.push_back(asteroidPtr);
		_generateAsteroid=fmod(rand(),8.0)+1;
		_entityClock->RestartAsteroidClock();
	}
}

void entityCreator::CreateSatellite()
{
	_timeSatellite=_entityClock->getSatelliteTime();
	if ((fmod(_timeSatellite,5)>0) && fmod(_timeSatellite,5)<(0.2) && Satellite::getNumberofSatellitesAlive() ==0 )
	{
		floatVector position =_playerPtr->getPosition();
		float angle =_playerPtr->getAngle();
		std::shared_ptr <Satellite> satellitePtr{ new Satellite{position,angle}};
		std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
		std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
		movingEntity::entityList.push_back(satellitePtr);
		movingEntity::entityList.push_back(satellitePtr2);
		movingEntity::entityList.push_back(satellitePtr3);
	}
}

void entityCreator::CreateLaser()
{
		_timeSatellite=_entityClock->getSatelliteTime();
	if ((fmod(_timeSatellite,10)>0) && fmod(_timeSatellite,10)<(0.2)  && LaserGenerator::getNumberofLasersAlive()==0)
	{
		std::shared_ptr <LaserGenerator> laserPtr{ new LaserGenerator{}};
		std::shared_ptr <LaserGenerator> laserPtr2= std::make_shared<LaserGenerator> (*laserPtr);
		movingEntity::entityList.push_back(laserPtr);
		movingEntity::entityList.push_back(laserPtr2);
		std::shared_ptr <LaserArc> arcPtr{ new LaserArc{laserPtr->getAngle(), laserPtr, laserPtr2}};
		movingEntity::entityList.push_back(arcPtr);
	}
}

void entityCreator::reset()
{
		_entityClock->RestartAsteroidClock();
		_generateAsteroid= fmod(rand(),5.0)+1;
		_generateEnemy= 1;
		_timeEnemy=0.0;
}