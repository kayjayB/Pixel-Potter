#include "Game.h"

Game::Game():
	_create(gameClock, MAXENEMIES, playerPtr)
{
	window.SplashScreen();
	_elapsedTime=0.0;
	_bulletExists=false;
	movingEntity::entityList.push_back(playerPtr);
	_timeAsteroid=0.0;
	_timeEnemy=0.0;
	_timeSatellite=0.0;
	window.setGameState(gameState::playing);
	generateAsteroid= fmod(rand(),5.0)+1;
	generateEnemy= 1;
}

Game::~Game()
{
}

void Game::createEnemies()
{
	
_timeEnemy+=gameClock->GetTime();
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

void Game::CreateAsteroid()
{

_timeAsteroid=gameClock->getAsteroidTime();
	if (_timeAsteroid > (generateAsteroid - 0.5) && _timeAsteroid < (generateAsteroid+0.5))
	{
		
		std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerPtr->getAngle()}};
		movingEntity::entityList.push_back(asteroidPtr);
		generateAsteroid=fmod(rand(),8.0)+1;
		gameClock->RestartAsteroidClock();
	}
}

void Game::CreateSatellite()
{
	_timeSatellite=gameClock->getSatelliteTime();
	if ((fmod(_timeSatellite,5)>0) && fmod(_timeSatellite,5)<(0.2) && Satellite::getNumberofSatellitesAlive() ==0 )
	{
		floatVector position =playerPtr->getPosition();
		float angle =playerPtr->getAngle();
		std::shared_ptr <Satellite> satellitePtr{ new Satellite{position,angle}};
		std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
		std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
		movingEntity::entityList.push_back(satellitePtr);
		movingEntity::entityList.push_back(satellitePtr2);
		movingEntity::entityList.push_back(satellitePtr3);
	}
}

void Game::Update()
{	
	userInput Keyevent =window.Update();
//	createEnemies();
	
//	CreateAsteroid();
	
//	CreateSatellite();
_create.create();

	playerPtr->Update(playerPtr->MovementDirection(Keyevent), GetTime());

int size= movingEntity::entityList.size();

// The for loop resizes dynamically since the size of the movingEntity::entityList vector is increasing
// as the enemy bullets are created
for (auto i =1; i< size; i++) 
{
	int sizeInitial= movingEntity::entityList.size();
	movingEntity::entityList[i]->Update(1, GetTime());
	int sizeFinal= movingEntity::entityList.size();
	if (sizeFinal>sizeInitial)
	{
		size+=1;
	}
}

	collision.checkCollision();

	collision.entityCleanUp(playerPtr, window);
	
	if ((Enemy::getTotalNumberofEnemies()%MAXENEMIES) == 0 && Enemy::getNumberofEnemiesAlive()==0 && Enemy::getTotalNumberofEnemies()!=0)
	{
		window.setGameState(gameState::win);

	}
	
	window.getGameState();

	
	if (window.reset==true)
	{
		Reset();
	}
	
	window.setLivesRemaining(playerPtr->getLives());
	window.setMaximumEnemies(MAXENEMIES);
	
}

void Game::Render()
{
	
	window.BeginDrawMain();

	
for (auto i= begin(movingEntity::entityList); i!=end(movingEntity::entityList);i++)
{
	window.show((*i));
}

//for (auto i=begin(entityManager::body); i!=end(entityManager::body); i++)
//{
//	window.show((**i));
//}
	
	window.EndDraw(); 
}

Window* Game::GetWindow()
{ 
	return &window; 
}

float Game::GetTime()
{ 
	return gameClock->GetTime();
}

void Game::RestartClock()
{ 
	gameClock->RestartClock();
}

void Game::Reset()
{

		movingEntity::entityList.clear();
		Enemy::ResetEnemies();
		playerPtr->reset();
		movingEntity::entityList.push_back(playerPtr);
		window.setGameState(gameState::playing);
		gameClock->RestartAsteroidClock();
		generateAsteroid= fmod(rand(),5.0)+1;
		generateEnemy= 1;
		Satellite::ResetSatellites();
}