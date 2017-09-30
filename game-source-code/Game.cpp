#include "Game.h"

Game::Game()
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
	
_timeEnemy+=_elapsedTime;
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

_timeAsteroid=gameClock.getAsteroidTime();
	if (_timeAsteroid > (generateAsteroid - 0.5) && _timeAsteroid < (generateAsteroid+0.5))
	{
		
		std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerPtr->getAngle()}};
		movingEntity::entityList.push_back(asteroidPtr);
		generateAsteroid=fmod(rand(),8.0)+1;
		gameClock.RestartAsteroidClock();
	}
}

void Game::CreateSatellite()
{
	_timeSatellite=gameClock.getSatelliteTime();
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
	
	createEnemies();
	
	CreateAsteroid();
	
	CreateSatellite();

	playerPtr->Update(playerPtr->MovementDirection(Keyevent), GetTime());

int size= movingEntity::entityList.size();

// The for loop resizes dynamically as the size of the movingEntity::entityList vector is increasing
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

	checkCollision();

	entityCleanUp();
	
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
	
	window.EndDraw(); 
}

Window* Game::GetWindow()
{ 
	return &window; 
}

float Game::GetTime()
{ 
	return gameClock.GetTime();
}

void Game::RestartClock()
{ 
	gameClock.RestartClock();
}

void Game::checkCollision()
{
	
for (int i=0; i<movingEntity::entityList.size();i++)

{
	for (int j =0 ; j< movingEntity::entityList.size() ;j++)
	{
		if (i!=j)
		{
		if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity && movingEntity::entityList[j]->getEntityType()== EntityList::EnemyEntity)
		{
		
			if (Collision(i,j))
			{
				movingEntity::entityList[i]->setLives(playerPtr->getLives() -1);
				movingEntity::entityList[j]->setLives(0);
			}
		}
			if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity && movingEntity::entityList[j]->getEntityType()== EntityList::AsteroidEntity)
			{
				if (Collision(i,j)) 
				{
					movingEntity::entityList[i]->setLives(playerPtr->getLives() -1);
					movingEntity::entityList[j]->setLives(0);
				}
			}
			
			if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity && movingEntity::entityList[j]->getEntityType()== EntityList::EnemyBulletEntity)
			{
				if (Collision(i,j)) 
				{
					movingEntity::entityList[i]->setLives(playerPtr->getLives() -1);
					movingEntity::entityList[j]->setLives(0);
				}
			}
			
			if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity && movingEntity::entityList[j]->getEntityType()== EntityList::EnemyBulletEntity)
			{
				if (Collision(i,j)) 
				{
					movingEntity::entityList[i]->setLives(0);
					movingEntity::entityList[j]->setLives(0);
				}
			}
			
			if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity && movingEntity::entityList[j]->getEntityType()== EntityList::EnemyEntity)
			{
				if (Collision(i,j)) 
				{
					movingEntity::entityList[i]->setLives(0);
					movingEntity::entityList[j]->setLives(0);
				}
			}
			
			if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity && movingEntity::entityList[j]->getEntityType()== EntityList::AsteroidEntity)
			{
				if (Collision(i,j)) 
				{
					movingEntity::entityList[i]->setLives(0);
				}
			}
			
			if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity && movingEntity::entityList[j]->getEntityType()== EntityList::SatelliteEntity)
			{
				if (Collision(i,j)) 
				{
					movingEntity::entityList[i]->setLives(0);
					movingEntity::entityList[j]->setLives(0);
				}
			}
		
		}
	}
}

}

bool Game::Collision(int i, int j)
{
		floatVector position1= movingEntity::entityList[i]->getPosition();
		floatVector position2= movingEntity::entityList[j]->getPosition();
		floatVector halfSize1=movingEntity::entityList[i]->getBodySize();
		floatVector halfSize2=movingEntity::entityList[j]->getBodySize();
//			
		float deltaX= position1[0]-position2[0];
		float deltaY= position1[1]-position2[1];
		float intersectX= fabs(deltaX)- (halfSize1[0]/2+halfSize2[0]/2);
		float intersectY= fabs(deltaY)- (halfSize1[1]/2+halfSize2[1]/2);
		
		if (intersectX < 0.0 && intersectY < 0.0)
		{
			return true;
		}
		
		return false;
}

void Game::entityCleanUp()
{
	if (playerPtr->getLives() <=0)
	{
		window.setGameState(gameState::lose);
		return;
	}
	for (auto i=begin(movingEntity::entityList); i!=end(movingEntity::entityList);)
	{
		if ((*i)->getLives() == 0)
		{
			movingEntity::entityList.erase(i);
		}
		else 
		{
			i++;
		}
	}
}

void Game::Reset()
{

		movingEntity::entityList.clear();
		Enemy::ResetEnemies();
		playerPtr->reset();
		movingEntity::entityList.push_back(playerPtr);
		window.setGameState(gameState::playing);
//		_clockAsteroid.restart();
//		_clockSatellite.restart();
		gameClock.RestartAsteroidClock();
		generateAsteroid= fmod(rand(),5.0)+1;
		generateEnemy= 1;
		Satellite::ResetSatellites();
}