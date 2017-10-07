#include "entityCreator.h"

entityCreator::entityCreator(std::shared_ptr <Clock> gameClock, int maxEnemies, std::shared_ptr <Player> playerPtr):
_entityClock{gameClock},
_playerPtr{playerPtr},
MAXENEMIES{maxEnemies}
{
	_timeAsteroid=0.0;
	_timeEnemy=0.0;
	_timeSatellite=0.0;
	generateAsteroid= fmod(rand(),5.0)+1;
	generateEnemy= 1;
}

entityCreator::~entityCreator()
{
}

void entityCreator::create()
{
	createEnemies();
	CreateAsteroid();
	CreateSatellite();
}

void entityCreator::createEnemies()
{
	
_timeEnemy+=_entityClock->GetTime();;
generateEnemy=fmod(rand(),4)+_timeEnemy;
if ( Enemy::getNumberofEnemiesAlive() < 3 )
	{
	if (_timeEnemy > (generateEnemy - 1) && _timeEnemy < (generateEnemy+1) && Enemy::getTotalNumberofEnemies()<MAXENEMIES)
	{
		std::shared_ptr <Enemy> enemyPtr{ new Enemy{}};
		movingEntity::entityList.push_back(enemyPtr);
	}
}
}

void entityCreator::CreateAsteroid()
{

_timeAsteroid=_entityClock->getAsteroidTime();
	if (_timeAsteroid > (generateAsteroid - 0.5) && _timeAsteroid < (generateAsteroid+0.5))
	{
		
		std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{_playerPtr->getAngle()}};
		movingEntity::entityList.push_back(asteroidPtr);
		generateAsteroid=fmod(rand(),8.0)+1;
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